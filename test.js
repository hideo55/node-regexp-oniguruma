var util = require('util');
var Onig = require('./index').Onig;

var str = 'cdbBdbsbz';
var p = new Onig("d(b+)(d)",'ig');

var res = p.exec(str);
console.log(util.inspect(res, true));

var re = new RegExp("d(b+)(d)",'ig');
res = re.exec(str);
console.log(util.inspect(res, true));

