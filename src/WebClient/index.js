const resultContainer = document.getElementById("result");

const loadResult = async (search) => {
  resultContainer.classList.remove("result--hidden");

  const inputContainer = resultContainer.querySelector(".result__input");
  const outputContainer = resultContainer.querySelector(".result__output");
  const form = resultContainer.querySelector(".result__form");

  const worker = new Worker("/assets/technicalc-worker.js");

  const { qsParse, Client } = await import("./imports");

  const setMml = (element, mml) => {
    element.classList.remove("result--loading");
    element.innerHTML = mml;

    if (window.MathJax != null) {
      MathJax.typeset();
    }
  };

  const setOutput = (result) => {
    const formData = new FormData(form);
    const style = {
      style: formData.get("style"),
      precision: Number(formData.get("precision")),
      digitGrouping: formData.get("digitGrouping") != null,
    };
    console.log(style);
    resultMml = Client.Value.toMml(result, style);
    setMml(outputContainer, resultMml);
  };

  const {
    elements,
    unitConversions = [],
    customAtoms = [],
    variables = [],
  } = qsParse(search);
  const encoded = { elements, unitConversions, customAtoms, variables };
  const editorValue = Client.Editor.decode(encoded);

  const inputMml = Client.Editor.toMml(editorValue);
  setMml(inputContainer, inputMml);

  const [parsingError, parsedValue] = Client.Editor.parse(editorValue);
  if (parsingError == null && parsedValue != null) {
    const work = Client.Work.calculate(parsedValue);
    worker.postMessage(work);
  }

  let result;
  worker.onmessage = (e) => {
    const value = e.data;
    if (value.error === true) {
      // Error
      outputContainer.innerHTML = "Error";
    } else {
      result = Client.Value.decode(value.results[0]);
      setOutput(result);
    }
  };

  form.addEventListener("change", () => {
    if (result != null) {
      setOutput(result);
    }
  });
};

const search = window.location.search.slice("?".length);

if (search.length !== 0) {
  loadResult(search);
}

document.addEventListener("click", (e) => {
  const { target } = e;
  if (target.classList.contains("result__close")) {
    resultContainer.remove();
  } else if (target.classList.contains("result__toggle-display-mode")) {
    resultContainer.classList.toggle("result--form-hidden");
  }
});
