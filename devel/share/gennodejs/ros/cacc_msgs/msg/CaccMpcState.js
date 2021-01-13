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

class CaccMpcState {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.F = null;
    }
    else {
      if (initObj.hasOwnProperty('F')) {
        this.F = initObj.F
      }
      else {
        this.F = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CaccMpcState
    // Serialize message field [F]
    bufferOffset = _serializer.float32(obj.F, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaccMpcState
    let len;
    let data = new CaccMpcState(null);
    // Deserialize message field [F]
    data.F = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 4;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/CaccMpcState';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '79de4254f7d72d7dd22d2ce8ed43faa2';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 F
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaccMpcState(null);
    if (msg.F !== undefined) {
      resolved.F = msg.F;
    }
    else {
      resolved.F = 0.0
    }

    return resolved;
    }
};

module.exports = CaccMpcState;
