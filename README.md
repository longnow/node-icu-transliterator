# node-icu-transliterator

This module provides node.js bindings for [Rule-Based Transliterators](http://userguide.icu-project.org/transforms/general#TOC-Rule-Based-Transliterators) in [ICU](http://site.icu-project.org/).

To install, you first need to have ICU installed and `icu-config` in your `PATH`. Then run:

```
$ npm install icu-transliterator
```

To use:

```javascript
let icuTransliterator = require('icu-transliterator');

let myRBT = icuTransliterator('a > b; b > a;', icuTransliterator.FORWARD);
myRBT.transliterate('abcd'); // -> 'bacd'
```

The first argument to the `icuTransliterator` constructor is a string containing the transliteration rules. The second argument is the direction, either `icuTransliterator.FORWARD` or `icuTransliterator.REVERSE`. If the second argument is omitted, it defaults to `icuTransliterator.FORWARD`.

The constructor returns an object that has a single method `transliterate`. It takes one argument, a string to transliterate, and returned the transliterated string.
