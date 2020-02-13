import React from "react";
import Svg from "react-native-svg/lib/module/elements/Svg";
import G from "react-native-svg/lib/module/elements/G";
import Rect from "react-native-svg/lib/module/elements/Rect";
import Path from "react-native-svg/lib/module/elements/Path";

const fillOpacities = {
  placeholder: 0.25,
  invalid: 0.5
};

export default ({ kind, attributes }, children, index) => {
  switch (kind) {
    case "svg":
      return attributes.xmlns != null
        ? // Top level svg - most props set in MathView
          React.createElement(Svg, null, children)
        : // Used as a clip mask
          // x/y attributes broken in rn-svg SVG elements so done in a G
          React.createElement(
            G,
            { key: index, x: attributes.x, y: attributes.y },
            React.createElement(
              Svg,
              {
                viewBox: attributes.viewBox,
                width: attributes.width,
                height: attributes.height
              },
              children
            )
          );
    case "g":
      return React.createElement(
        G,
        {
          key: index,
          transform: attributes.transform,
          fillOpacity:
            attributes.class != null
              ? fillOpacities[attributes.class.trim()]
              : undefined
        },
        children
      );
    case "path":
      return React.createElement(Path, {
        key: index,
        d: attributes.d,
        transform: attributes.transform // for brackets
      });
    case "rect":
      return React.createElement(Rect, {
        key: index,
        x: attributes.x,
        y: attributes.y,
        width: attributes.width,
        height: attributes.height
      });
    default:
      throw new Error(`Unknown element ${kind}`);
  }
};
