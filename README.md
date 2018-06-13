# node-icu-transliterator

This module provides node.js bindings for [ICU](http://site.icu-project.org/)’s [Rule-Based Transliterators](http://userguide.icu-project.org/transforms/general#TOC-Rule-Based-Transliterators) and [Rule-Based Number Formats](http://userguide.icu-project.org/formatparse/numbers).

To install, you first need to have ICU installed and `icu-config` in your `PATH`. Then run:

```
$ npm install icu-transliterator
```

## Rule-Based Transliterators

Example:

```javascript
let RBT = require('icu-transliterator').RBT;

let myRBT = RBT('a > b; b > a;', RBT.FORWARD);
myRBT.transliterate('abcd'); // -> 'bacd'
```

The first argument to the `RBT` constructor is a string containing the transliteration rules. The second argument is the direction, either `RBT.FORWARD` or `RBT.REVERSE`. If the second argument is omitted, it defaults to `RBT.FORWARD`.

The constructor returns an object that has a single method `transliterate`. It takes one argument, a string to transliterate, and returned the transliterated string.

## Rule-Based Number Formats

Example:

```javascript
let RBNF = require('icu-transliterator').RBNF;

let myRBNF = RBNF('-x: minus >>; x.x: << point >>; zero; one; two; three; four; five; six;     seven; eight; nine; 10: << >>; 100: << >>>; 1000: <<, >>>; 1,000,000: <<, >>>; 1,000,000,000: <<, >>>; 1,000,000,000,000: <<, >>>; 1,000,000,000,000,000: =#,##0=; ');
myRBNF.format(1.1); // -> 'one point one'
```

The argument to the `RBNF` constructor is a string containing the number format rules. The constructor returns an object that has a single method `format`. It takes one argument, a number to format, and returned the formatted string.
