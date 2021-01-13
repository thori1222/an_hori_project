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

class CaccControlPacket {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.vel_ref = null;
      this.acc_ref = null;
      this.checksum = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('vel_ref')) {
        this.vel_ref = initObj.vel_ref
      }
      else {
        this.vel_ref = 0.0;
      }
      if (initObj.hasOwnProperty('acc_ref')) {
        this.acc_ref = initObj.acc_ref
      }
      else {
        this.acc_ref = 0.0;
      }
      if (initObj.hasOwnProperty('checksum')) {
        this.checksum = initObj.checksum
      }
      else {
        this.checksum = 0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CaccControlPacket
    // Serialize message field [id]
    bufferOffset = _serializer.int16(obj.id, buffer, bufferOffset);
    // Serialize message field [vel_ref]
    bufferOffset = _serializer.float32(obj.vel_ref, buffer, bufferOffset);
    // Serialize message field [acc_ref]
    bufferOffset = _serializer.float32(obj.acc_ref, buffer, bufferOffset);
    // Serialize message field [checksum]
    bufferOffset = _serializer.uint32(obj.checksum, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaccControlPacket
    let len;
    let data = new CaccControlPacket(null);
    // Deserialize message field [id]
    data.id = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [vel_ref]
    data.vel_ref = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acc_ref]
    data.acc_ref = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [checksum]
    data.checksum = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 14;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/CaccControlPacket';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ca73aaf0f9afa68bd8dfa673d8298a2c';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 id
    float32 vel_ref
    float32 acc_ref
    
    uint32 checksum
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaccControlPacket(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.vel_ref !== undefined) {
      resolved.vel_ref = msg.vel_ref;
    }
    else {
      resolved.vel_ref = 0.0
    }

    if (msg.acc_ref !== undefined) {
      resolved.acc_ref = msg.acc_ref;
    }
    else {
      resolved.acc_ref = 0.0
    }

    if (msg.checksum !== undefined) {
      resolved.checksum = msg.checksum;
    }
    else {
      resolved.checksum = 0
    }

    return resolved;
    }
};

module.exports = CaccControlPacket;
