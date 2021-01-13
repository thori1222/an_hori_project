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

class PrarxParam {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.theta1 = null;
      this.theta2 = null;
      this.eta = null;
      this.scale = null;
    }
    else {
      if (initObj.hasOwnProperty('theta1')) {
        this.theta1 = initObj.theta1
      }
      else {
        this.theta1 = [];
      }
      if (initObj.hasOwnProperty('theta2')) {
        this.theta2 = initObj.theta2
      }
      else {
        this.theta2 = [];
      }
      if (initObj.hasOwnProperty('eta')) {
        this.eta = initObj.eta
      }
      else {
        this.eta = [];
      }
      if (initObj.hasOwnProperty('scale')) {
        this.scale = initObj.scale
      }
      else {
        this.scale = [];
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type PrarxParam
    // Serialize message field [theta1]
    bufferOffset = _arraySerializer.float32(obj.theta1, buffer, bufferOffset, null);
    // Serialize message field [theta2]
    bufferOffset = _arraySerializer.float32(obj.theta2, buffer, bufferOffset, null);
    // Serialize message field [eta]
    bufferOffset = _arraySerializer.float32(obj.eta, buffer, bufferOffset, null);
    // Serialize message field [scale]
    bufferOffset = _arraySerializer.float32(obj.scale, buffer, bufferOffset, null);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type PrarxParam
    let len;
    let data = new PrarxParam(null);
    // Deserialize message field [theta1]
    data.theta1 = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [theta2]
    data.theta2 = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [eta]
    data.eta = _arrayDeserializer.float32(buffer, bufferOffset, null)
    // Deserialize message field [scale]
    data.scale = _arrayDeserializer.float32(buffer, bufferOffset, null)
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += 4 * object.theta1.length;
    length += 4 * object.theta2.length;
    length += 4 * object.eta.length;
    length += 4 * object.scale.length;
    return length + 16;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/PrarxParam';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '50e5d6a7f9d855220ccc7cbcc9f77398';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32[] theta1
    float32[] theta2
    float32[] eta
    float32[] scale
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new PrarxParam(null);
    if (msg.theta1 !== undefined) {
      resolved.theta1 = msg.theta1;
    }
    else {
      resolved.theta1 = []
    }

    if (msg.theta2 !== undefined) {
      resolved.theta2 = msg.theta2;
    }
    else {
      resolved.theta2 = []
    }

    if (msg.eta !== undefined) {
      resolved.eta = msg.eta;
    }
    else {
      resolved.eta = []
    }

    if (msg.scale !== undefined) {
      resolved.scale = msg.scale;
    }
    else {
      resolved.scale = []
    }

    return resolved;
    }
};

module.exports = PrarxParam;
