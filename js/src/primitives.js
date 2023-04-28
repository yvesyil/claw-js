const ref = require('ref-napi');
const StructTypeModule = require('ref-struct-di');
const ArrayTypeModule = require('ref-array-di');

const StructType = StructTypeModule(ref);
const ArrayType = ArrayTypeModule(ref);

const _type = {
  'CLAW_INT8': 0,
  'CLAW_UINT8': 1,
  'CLAW_INT16': 2,
  'CLAW_UINT16': 3,
  'CLAW_INT32': 4,
  'CLAW_UINT32': 5,
  'CLAW_INT64': 6,
  'CLAW_UINT64': 7,
  'CLAW_FLT32': 8,
  'CLAW_FLT64': 9,
};

const _dlen_arr = ArrayType(ref.types.ulonglong, 2);

const _mat = StructType({
  data: ref.refType(ref.types.void),
  dtype: ref.types.int,
  dlen: _dlen_arr
});

const _mat_ptr = ref.refType(_mat);

module.exports = {
  _type,
  _dlen_arr,
  _mat,
  _mat_ptr,
};