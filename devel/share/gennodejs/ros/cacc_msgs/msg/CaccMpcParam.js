// Auto-generated. Do not edit!

// (in-package cacc_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class CaccMpcParam {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.Ds = null;
      this.Dmin = null;
      this.umax = null;
      this.umin = null;
      this.sf0 = null;
      this.sf1 = null;
      this.sf2 = null;
      this.q0 = null;
      this.q1 = null;
      this.q2 = null;
      this.r = null;
      this.su = null;
      this.sd = null;
      this.tf = null;
      this.ht = null;
      this.dv = null;
      this.zeta = null;
      this.kmax = null;
    }
    else {
      if (initObj.hasOwnProperty('Ds')) {
        this.Ds = initObj.Ds
      }
      else {
        this.Ds = 0.0;
      }
      if (initObj.hasOwnProperty('Dmin')) {
        this.Dmin = initObj.Dmin
      }
      else {
        this.Dmin = 0.0;
      }
      if (initObj.hasOwnProperty('umax')) {
        this.umax = initObj.umax
      }
      else {
        this.umax = 0.0;
      }
      if (initObj.hasOwnProperty('umin')) {
        this.umin = initObj.umin
      }
      else {
        this.umin = 0.0;
      }
      if (initObj.hasOwnProperty('sf0')) {
        this.sf0 = initObj.sf0
      }
      else {
        this.sf0 = 0;
      }
      if (initObj.hasOwnProperty('sf1')) {
        this.sf1 = initObj.sf1
      }
      else {
        this.sf1 = 0;
      }
      if (initObj.hasOwnProperty('sf2')) {
        this.sf2 = initObj.sf2
      }
      else {
        this.sf2 = 0;
      }
      if (initObj.hasOwnProperty('q0')) {
        this.q0 = initObj.q0
      }
      else {
        this.q0 = 0;
      }
      if (initObj.hasOwnProperty('q1')) {
        this.q1 = initObj.q1
      }
      else {
        this.q1 = 0;
      }
      if (initObj.hasOwnProperty('q2')) {
        this.q2 = initObj.q2
      }
      else {
        this.q2 = 0;
      }
      if (initObj.hasOwnProperty('r')) {
        this.r = initObj.r
      }
      else {
        this.r = 0;
      }
      if (initObj.hasOwnProperty('su')) {
        this.su = initObj.su
      }
      else {
        this.su = 0;
      }
      if (initObj.hasOwnProperty('sd')) {
        this.sd = initObj.sd
      }
      else {
        this.sd = 0;
      }
      if (initObj.hasOwnProperty('tf')) {
        this.tf = initObj.tf
      }
      else {
        this.tf = 0.0;
      }
      if (initObj.hasOwnProperty('ht')) {
        this.ht = initObj.ht
      }
      else {
        this.ht = 0.0;
      }
      if (initObj.hasOwnProperty('dv')) {
        this.dv = initObj.dv
      }
      else {
        this.dv = 0;
      }
      if (initObj.hasOwnProperty('zeta')) {
        this.zeta = initObj.zeta
      }
      else {
        this.zeta = 0;
      }
      if (initObj.hasOwnProperty('kmax')) {
        this.kmax = initObj.kmax
      }
      else {
        this.kmax = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CaccMpcParam
    // Serialize message field [Ds]
    bufferOffset = _serializer.float32(obj.Ds, buffer, bufferOffset);
    // Serialize message field [Dmin]
    bufferOffset = _serializer.float32(obj.Dmin, buffer, bufferOffset);
    // Serialize message field [umax]
    bufferOffset = _serializer.float32(obj.umax, buffer, bufferOffset);
    // Serialize message field [umin]
    bufferOffset = _serializer.float32(obj.umin, buffer, bufferOffset);
    // Serialize message field [sf0]
    bufferOffset = _serializer.int32(obj.sf0, buffer, bufferOffset);
    // Serialize message field [sf1]
    bufferOffset = _serializer.int32(obj.sf1, buffer, bufferOffset);
    // Serialize message field [sf2]
    bufferOffset = _serializer.int32(obj.sf2, buffer, bufferOffset);
    // Serialize message field [q0]
    bufferOffset = _serializer.int32(obj.q0, buffer, bufferOffset);
    // Serialize message field [q1]
    bufferOffset = _serializer.int32(obj.q1, buffer, bufferOffset);
    // Serialize message field [q2]
    bufferOffset = _serializer.int32(obj.q2, buffer, bufferOffset);
    // Serialize message field [r]
    bufferOffset = _serializer.int32(obj.r, buffer, bufferOffset);
    // Serialize message field [su]
    bufferOffset = _serializer.int32(obj.su, buffer, bufferOffset);
    // Serialize message field [sd]
    bufferOffset = _serializer.int32(obj.sd, buffer, bufferOffset);
    // Serialize message field [tf]
    bufferOffset = _serializer.float32(obj.tf, buffer, bufferOffset);
    // Serialize message field [ht]
    bufferOffset = _serializer.float32(obj.ht, buffer, bufferOffset);
    // Serialize message field [dv]
    bufferOffset = _serializer.int16(obj.dv, buffer, bufferOffset);
    // Serialize message field [zeta]
    bufferOffset = _serializer.int16(obj.zeta, buffer, bufferOffset);
    // Serialize message field [kmax]
    bufferOffset = _serializer.int16(obj.kmax, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaccMpcParam
    let len;
    let data = new CaccMpcParam(null);
    // Deserialize message field [Ds]
    data.Ds = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [Dmin]
    data.Dmin = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [umax]
    data.umax = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [umin]
    data.umin = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sf0]
    data.sf0 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sf1]
    data.sf1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sf2]
    data.sf2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [q0]
    data.q0 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [q1]
    data.q1 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [q2]
    data.q2 = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [r]
    data.r = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [su]
    data.su = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [sd]
    data.sd = _deserializer.int32(buffer, bufferOffset);
    // Deserialize message field [tf]
    data.tf = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [ht]
    data.ht = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [dv]
    data.dv = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [zeta]
    data.zeta = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [kmax]
    data.kmax = _deserializer.int16(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 66;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/CaccMpcParam';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '520e747c091a36b66d7fea5adeed4945';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 Ds
    float32 Dmin
    float32 umax
    float32 umin
    
    int32   sf0
    int32   sf1
    int32   sf2
    int32   q0
    int32   q1
    int32   q2
    int32   r
    int32   su
    int32   sd
    
    float32 tf
    float32 ht
    int16   dv
    int16   zeta
    int16   kmax
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaccMpcParam(null);
    if (msg.Ds !== undefined) {
      resolved.Ds = msg.Ds;
    }
    else {
      resolved.Ds = 0.0
    }

    if (msg.Dmin !== undefined) {
      resolved.Dmin = msg.Dmin;
    }
    else {
      resolved.Dmin = 0.0
    }

    if (msg.umax !== undefined) {
      resolved.umax = msg.umax;
    }
    else {
      resolved.umax = 0.0
    }

    if (msg.umin !== undefined) {
      resolved.umin = msg.umin;
    }
    else {
      resolved.umin = 0.0
    }

    if (msg.sf0 !== undefined) {
      resolved.sf0 = msg.sf0;
    }
    else {
      resolved.sf0 = 0
    }

    if (msg.sf1 !== undefined) {
      resolved.sf1 = msg.sf1;
    }
    else {
      resolved.sf1 = 0
    }

    if (msg.sf2 !== undefined) {
      resolved.sf2 = msg.sf2;
    }
    else {
      resolved.sf2 = 0
    }

    if (msg.q0 !== undefined) {
      resolved.q0 = msg.q0;
    }
    else {
      resolved.q0 = 0
    }

    if (msg.q1 !== undefined) {
      resolved.q1 = msg.q1;
    }
    else {
      resolved.q1 = 0
    }

    if (msg.q2 !== undefined) {
      resolved.q2 = msg.q2;
    }
    else {
      resolved.q2 = 0
    }

    if (msg.r !== undefined) {
      resolved.r = msg.r;
    }
    else {
      resolved.r = 0
    }

    if (msg.su !== undefined) {
      resolved.su = msg.su;
    }
    else {
      resolved.su = 0
    }

    if (msg.sd !== undefined) {
      resolved.sd = msg.sd;
    }
    else {
      resolved.sd = 0
    }

    if (msg.tf !== undefined) {
      resolved.tf = msg.tf;
    }
    else {
      resolved.tf = 0.0
    }

    if (msg.ht !== undefined) {
      resolved.ht = msg.ht;
    }
    else {
      resolved.ht = 0.0
    }

    if (msg.dv !== undefined) {
      resolved.dv = msg.dv;
    }
    else {
      resolved.dv = 0
    }

    if (msg.zeta !== undefined) {
      resolved.zeta = msg.zeta;
    }
    else {
      resolved.zeta = 0
    }

    if (msg.kmax !== undefined) {
      resolved.kmax = msg.kmax;
    }
    else {
      resolved.kmax = 0
    }

    return resolved;
    }
};

module.exports = CaccMpcParam;
