# node-icu-transliterator

This module provides node.js bindings for [ICU](http://site.icu-project.org/)’s [Rule-Based Transliterators](http://userguide.icu-project.org/transforms/general#TOC-Rule-Based-Transliterators) and [Rule-Based Number Formats](http://userguide.icu-project.org/formatparse/numbers).

To install the module, you need to have ICU installed and accessible to `pkg-config`. The module is published on NPM as `icu-transliterator`.

On OS X, you can install ICU with [Homebrew](http://brew.sh) by running `brew install icu4c`. You can add it to the `pkg-config` path with `export PKG_CONFIG_PATH=/usr/local/opt/icu4c/lib/pkgconfig`.

## Rule-Based Transliterators

Example:

```javascript
let RBT = require('icu-transliterator').RBT;

let myRBT = RBT('Latin-Cyrillic', RBT.FORWARD);
myRBT.transliterate('mir'); // -> 'мир'

let myRBT = RBT.fromRules('a > b; b > a;', RBT.FORWARD);
myRBT.transliterate('abcd'); // -> 'bacd'

RBT.register('foo', 'a > c; b > d;');
let myRBT = RBT('foo', RBT.FORWARD);
myRBT.transliterate('abcd'); // -> 'cdcd'

```

`RBT(id, dir)` creates a transliterator from an ICU transliterator ID. The first argument is the ID. The optional second argument is the direction, either `RBT.FORWARD` (default) or `RBT.REVERSE`.

`RBT.fromRules(rules, dir)` creates a transliterator from a rules string. The first argument is rules string and the second argument is the direction, either `RBT.FORWARD` or `RBT.REVERSE`. If the second argument is omitted, it defaults to `RBT.FORWARD`.

The returned transliterator object has a single method `transliterate`. It takes one argument, a string to transliterate, and returns the transliterated string.

`RBT.register(id, rules)` registers a new transliterator with ICU. The first argument is the new ID and the second argument is the rules string. Once registered, you can access the transliterator with `RBT(id, dir)`.

## Rule-Based Number Formats

Example:

```javascript
let RBNF = require('icu-transliterator').RBNF;

let myRBNF = RBNF('eng');
myRBNF.format(14); //  -> 'fourteen'

let myRBNF = RBNF('eng', RBNF.ORDINAL);
myRBNF.format(14); //  -> '14th'

let myRBNF = RBNF.fromRules('-x: minus >>; x.x: << point >>; zero; one; two; three; four; five; six; seven; eight; nine; 10: << >>; 100: << >>>; 1000: <<, >>>; 1,000,000: <<, >>>; 1,000,000,000: <<, >>>; 1,000,000,000,000: <<, >>>; 1,000,000,000,000,000: =#,##0=; ');
myRBNF.format(1.1); // -> 'one point one'
```

`RBNF(language, tag)` creates a number formatter for a built-in ICU locale. The first is the language code (ISO 639 alpha-2 or alpha-3). The optional second argument is one of `RBNF.SPELLOUT` (default), `RBNF.ORDINAL`, `RBNF.DURATION`, or `RBNF.NUMBERING_SYSTEM`.

`RBNF.fromRules(rules)` creates a number formatter from the passed-in rules string.

The returned formatter object has a single method `format`. It takes one argument, a number to format, and returns the formatted string.
