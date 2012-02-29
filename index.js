var util = require('util');
var onig = require('./build/Release/oniguruma').Onig;
//util.inherits(onig, RegExp);
exports.Onig = onig;