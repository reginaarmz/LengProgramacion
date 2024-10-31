obj2indent
==========

[![Build Status](http://img.shields.io/travis/tsuyoshiwada/obj2indent.svg?style=flat-square)](https://travis-ci.org/tsuyoshiwada/obj2indent)
[![npm version](https://img.shields.io/npm/v/obj2indent.svg?style=flat-square)](http://badge.fury.io/js/obj2indent)
[![Bower](https://img.shields.io/bower/v/obj2indent.svg?style=flat-square)](http://bower.io/search/?q=obj2indent)
[![License](https://img.shields.io/badge/license-MIT-blue.svg?style=flat-square)](https://raw.githubusercontent.com/tsuyoshiwada/obj2indent/master/LICENSE)


Convert a JavaScript object to a string used the indentation.  
[indent2obj.js](https://github.com/tsuyoshiwada/indent2obj) and interconvertible.


## Install

### npm

```
$ npm install obj2indent
```

### bower

```
$ bower install obj2indent
```

### Basic

1. Download the [obj2indent.min.js](https://raw.githubusercontent.com/tsuyoshiwada/obj2indent/master/obj2indent.min.js).  
2. Load it in the script tag.


```html
<script type="text/javascript" src="obj2indent.min.js"></script>
```



## Usage

```javascript
var results = obj2indent([
  {
    name: "depth1",
    children: [
      {
        name: "depth2",
        children: []
      },
      {
        name: "depth2",
        children: [
          {
            name: "depth3"
          }
        ]
      }
    ]
  },
  {
    name: "depth1"
  },
  {
    name: "depth1",
    children: [
      {
        name: "depth2"
      }
    ]
  }
]);

console.log(results);
/*
depth1
  depth2
  depth2
    depth3
depth1
depth1
  dpeth2
*/
```


### Change indent types

The default is to use 2 spaces.  
If you want to the tab, Do the following.

```javascript
obj2indent(input, "\t");
```

In the case of the 4 spaces.

```javascript
obj2indent(input, "    ");
```


## Settings

```javascript
obj2indent.defaultIndent = "  ";

obj2indent.keys = {
  name: "name",
  children: "children"
};
```



## Browser Support

* IE6 +
* Chrome
* Firefox
* Safari
* iOS
* Android


## License
Released under the [MIT Licence](https://raw.githubusercontent.com/tsuyoshiwada/indent2obj/master/LICENSE)


## Author
[tsuyoshi wada](https://github.com/tsuyoshiwada/)
