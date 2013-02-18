# node-oniguruma

  Node.js binding of Oniguruma that Regular Expresion Library.
  This is experimental implementation.

## Usage

```javascript
var Onig = require('oniguruma').Onig;

var str = 'cdbBdbsbz';
var p = new Onig("d(b+)(d)", 'ig');

var res = p.exec(str);
```

## API

### new Onig()

### exec()

### test()

## Constants

### SYNTAX_ASIS
### SYNTAX_POSIX_BASIC
### SYNTAX_POSIX_EXTENDED
### SYNTAX_EMACS
### SYNTAX_GREP
### SYNTAX_GNU
### SYNTAX_JAVA
### SYNTAX_PERL
### SYNTAX_PERL_NG
### SYNTAX_RUBY

## License 

(The MIT License)

Copyright (c) 2011 Hideaki Ohno &lt;hide.o.j55{at}gmail.com&gt;

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
