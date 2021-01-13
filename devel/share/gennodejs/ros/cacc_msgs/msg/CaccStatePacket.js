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

class CaccStatePacket {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.manual = null;
      this.activated = null;
      this.thw = null;
      this.alpha = null;
      this.beta = null;
      this.vel_gain = null;
      this.vel_gain_low = null;
      this.vel_gain_dec = null;
      this.distance = null;
      this.speed = null;
      this.acceleration = null;
    }
    else {
      if (initObj.hasOwnProperty('id')) {
        this.id = initObj.id
      }
      else {
        this.id = 0;
      }
      if (initObj.hasOwnProperty('manual')) {
        this.manual = initObj.manual
      }
      else {
        this.manual = false;
      }
      if (initObj.hasOwnProperty('activated')) {
        this.activated = initObj.activated
      }
      else {
        this.activated = false;
      }
      if (initObj.hasOwnProperty('thw')) {
        this.thw = initObj.thw
      }
      else {
        this.thw = 0.0;
      }
      if (initObj.hasOwnProperty('alpha')) {
        this.alpha = initObj.alpha
      }
      else {
        this.alpha = 0.0;
      }
      if (initObj.hasOwnProperty('beta')) {
        this.beta = initObj.beta
      }
      else {
        this.beta = 0.0;
      }
      if (initObj.hasOwnProperty('vel_gain')) {
        this.vel_gain = initObj.vel_gain
      }
      else {
        this.vel_gain = 0;
      }
      if (initObj.hasOwnProperty('vel_gain_low')) {
        this.vel_gain_low = initObj.vel_gain_low
      }
      else {
        this.vel_gain_low = 0;
      }
      if (initObj.hasOwnProperty('vel_gain_dec')) {
        this.vel_gain_dec = initObj.vel_gain_dec
      }
      else {
        this.vel_gain_dec = 0;
      }
      if (initObj.hasOwnProperty('distance')) {
        this.distance = initObj.distance
      }
      else {
        this.distance = 0.0;
      }
      if (initObj.hasOwnProperty('speed')) {
        this.speed = initObj.speed
      }
      else {
        this.speed = 0.0;
      }
      if (initObj.hasOwnProperty('acceleration')) {
        this.acceleration = initObj.acceleration
      }
      else {
        this.acceleration = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type CaccStatePacket
    // Serialize message field [id]
    bufferOffset = _serializer.int16(obj.id, buffer, bufferOffset);
    // Serialize message field [manual]
    bufferOffset = _serializer.bool(obj.manual, buffer, bufferOffset);
    // Serialize message field [activated]
    bufferOffset = _serializer.bool(obj.activated, buffer, bufferOffset);
    // Serialize message field [thw]
    bufferOffset = _serializer.float32(obj.thw, buffer, bufferOffset);
    // Serialize message field [alpha]
    bufferOffset = _serializer.float32(obj.alpha, buffer, bufferOffset);
    // Serialize message field [beta]
    bufferOffset = _serializer.float32(obj.beta, buffer, bufferOffset);
    // Serialize message field [vel_gain]
    bufferOffset = _serializer.int16(obj.vel_gain, buffer, bufferOffset);
    // Serialize message field [vel_gain_low]
    bufferOffset = _serializer.int16(obj.vel_gain_low, buffer, bufferOffset);
    // Serialize message field [vel_gain_dec]
    bufferOffset = _serializer.int16(obj.vel_gain_dec, buffer, bufferOffset);
    // Serialize message field [distance]
    bufferOffset = _serializer.float32(obj.distance, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [acceleration]
    bufferOffset = _serializer.float32(obj.acceleration, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaccStatePacket
    let len;
    let data = new CaccStatePacket(null);
    // Deserialize message field [id]
    data.id = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [manual]
    data.manual = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [activated]
    data.activated = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [thw]
    data.thw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [alpha]
    data.alpha = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [beta]
    data.beta = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vel_gain]
    data.vel_gain = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [vel_gain_low]
    data.vel_gain_low = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [vel_gain_dec]
    data.vel_gain_dec = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [distance]
    data.distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acceleration]
    data.acceleration = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 34;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/CaccStatePacket';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'd1e7f03c3be6f5504cfdc21bdc1d3462';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    int16 id
    bool manual #1: manual. 0: automated
    bool activated #1: activated, 0: non-activated (ghost-manual)
    #int16 order
    float32 thw
    float32 alpha
    float32 beta
    int16 vel_gain
    int16 vel_gain_low
    int16 vel_gain_dec
    float32 distance
    float32 speed
    float32 acceleration
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaccStatePacket(null);
    if (msg.id !== undefined) {
      resolved.id = msg.id;
    }
    else {
      resolved.id = 0
    }

    if (msg.manual !== undefined) {
      resolved.manual = msg.manual;
    }
    else {
      resolved.manual = false
    }

    if (msg.activated !== undefined) {
      resolved.activated = msg.activated;
    }
    else {
      resolved.activated = false
    }

    if (msg.thw !== undefined) {
      resolved.thw = msg.thw;
    }
    else {
      resolved.thw = 0.0
    }

    if (msg.alpha !== undefined) {
      resolved.alpha = msg.alpha;
    }
    else {
      resolved.alpha = 0.0
    }

    if (msg.beta !== undefined) {
      resolved.beta = msg.beta;
    }
    else {
      resolved.beta = 0.0
    }

    if (msg.vel_gain !== undefined) {
      resolved.vel_gain = msg.vel_gain;
    }
    else {
      resolved.vel_gain = 0
    }

    if (msg.vel_gain_low !== undefined) {
      resolved.vel_gain_low = msg.vel_gain_low;
    }
    else {
      resolved.vel_gain_low = 0
    }

    if (msg.vel_gain_dec !== undefined) {
      resolved.vel_gain_dec = msg.vel_gain_dec;
    }
    else {
      resolved.vel_gain_dec = 0
    }

    if (msg.distance !== undefined) {
      resolved.distance = msg.distance;
    }
    else {
      resolved.distance = 0.0
    }

    if (msg.speed !== undefined) {
      resolved.speed = msg.speed;
    }
    else {
      resolved.speed = 0.0
    }

    if (msg.acceleration !== undefined) {
      resolved.acceleration = msg.acceleration;
    }
    else {
      resolved.acceleration = 0.0
    }

    return resolved;
    }
};

module.exports = CaccStatePacket;
