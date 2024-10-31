/*!
 * obj2indent
 * 
 * @version 0.0.1
 * @license MIT
 * @author tsuyoshiwada
 * @url https://github.com/tsuyoshiwada/obj2indent
 */
(function(root){
  "use strict";


  function hasProp(obj, key){
    return Object.prototype.hasOwnProperty.call(obj, key);
  }


  // http://hg.mozilla.org/mozilla-central/diff/7c3cb4883157/js/src/builtin/String.js
  function strRepeat(str, n){
    var result = "";
    for( ;; ){
      if( n & 1 ) result += str;
      n >>= 1;
      if( n ) str += str;
      else break;
    }
    return result;
  }


  function toIndentArray(input, indent, depth){
    var results = [],
        result,
        keys = obj2indent.keys,
        keyName = keys.name,
        keyChildren = keys.children,
        l = input.length, i, row;

    for( i = 0; i < l; i++ ){
      row = input[i];
      if( !hasProp(row, keyName) ) continue;
      results.push(strRepeat(indent, depth) + row[keyName]);
      if( hasProp(row, keyChildren) && row[keyChildren].length ){
        result = toIndentArray(row[keyChildren], indent, depth + 1);
        if( result.length > 0 ){
          results = results.concat(result);
        }
      }
    }

    return results;
  }


  function obj2indent(input, indent){
    return toIndentArray(input, indent || obj2indent.defaultIndent, 0).join("\n");
  }


  // default settings
  obj2indent.defaultIndent = "  ";
  obj2indent.keys = {
    name: "name",
    children: "children"
  };


  // export modules
  if( typeof module === "object" && typeof module.exports === "object" ){
    module.exports = obj2indent;

  /* global define */
  }else if( typeof define === "function" && define.amd ){
    define("obj2indent", obj2indent);

  }else{
    root.obj2indent = obj2indent;
  }

}(this));