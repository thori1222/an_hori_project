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

class CaccSensorPacket {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.id = null;
      this.manual = null;
      this.thw = null;
      this.alpha = null;
      this.beta = null;
      this.sensor2frontbumper = null;
      this.sensor2rearbumper = null;
      this.vel_gain = null;
      this.vel_gain_low = null;
      this.vel_gain_dec = null;
      this.x = null;
      this.y = null;
      this.u = null;
      this.v = null;
      this.yaw = null;
      this.speed = null;
      this.acceleration = null;
      this.front_x = null;
      this.front_y = null;
      this.front_u = null;
      this.front_v = null;
      this.front_yaw = null;
      this.front_speed = null;
      this.front_acceleration = null;
      this.front_distance = null;
      this.rear_x = null;
      this.rear_y = null;
      this.rear_u = null;
      this.rear_v = null;
      this.rear_yaw = null;
      this.rear_speed = null;
      this.rear_acceleration = null;
      this.rear_distance = null;
      this.checksum = null;
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
      if (initObj.hasOwnProperty('sensor2frontbumper')) {
        this.sensor2frontbumper = initObj.sensor2frontbumper
      }
      else {
        this.sensor2frontbumper = 0.0;
      }
      if (initObj.hasOwnProperty('sensor2rearbumper')) {
        this.sensor2rearbumper = initObj.sensor2rearbumper
      }
      else {
        this.sensor2rearbumper = 0.0;
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
      if (initObj.hasOwnProperty('x')) {
        this.x = initObj.x
      }
      else {
        this.x = 0.0;
      }
      if (initObj.hasOwnProperty('y')) {
        this.y = initObj.y
      }
      else {
        this.y = 0.0;
      }
      if (initObj.hasOwnProperty('u')) {
        this.u = initObj.u
      }
      else {
        this.u = 0.0;
      }
      if (initObj.hasOwnProperty('v')) {
        this.v = initObj.v
      }
      else {
        this.v = 0.0;
      }
      if (initObj.hasOwnProperty('yaw')) {
        this.yaw = initObj.yaw
      }
      else {
        this.yaw = 0.0;
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
      if (initObj.hasOwnProperty('front_x')) {
        this.front_x = initObj.front_x
      }
      else {
        this.front_x = 0.0;
      }
      if (initObj.hasOwnProperty('front_y')) {
        this.front_y = initObj.front_y
      }
      else {
        this.front_y = 0.0;
      }
      if (initObj.hasOwnProperty('front_u')) {
        this.front_u = initObj.front_u
      }
      else {
        this.front_u = 0.0;
      }
      if (initObj.hasOwnProperty('front_v')) {
        this.front_v = initObj.front_v
      }
      else {
        this.front_v = 0.0;
      }
      if (initObj.hasOwnProperty('front_yaw')) {
        this.front_yaw = initObj.front_yaw
      }
      else {
        this.front_yaw = 0.0;
      }
      if (initObj.hasOwnProperty('front_speed')) {
        this.front_speed = initObj.front_speed
      }
      else {
        this.front_speed = 0.0;
      }
      if (initObj.hasOwnProperty('front_acceleration')) {
        this.front_acceleration = initObj.front_acceleration
      }
      else {
        this.front_acceleration = 0.0;
      }
      if (initObj.hasOwnProperty('front_distance')) {
        this.front_distance = initObj.front_distance
      }
      else {
        this.front_distance = 0.0;
      }
      if (initObj.hasOwnProperty('rear_x')) {
        this.rear_x = initObj.rear_x
      }
      else {
        this.rear_x = 0.0;
      }
      if (initObj.hasOwnProperty('rear_y')) {
        this.rear_y = initObj.rear_y
      }
      else {
        this.rear_y = 0.0;
      }
      if (initObj.hasOwnProperty('rear_u')) {
        this.rear_u = initObj.rear_u
      }
      else {
        this.rear_u = 0.0;
      }
      if (initObj.hasOwnProperty('rear_v')) {
        this.rear_v = initObj.rear_v
      }
      else {
        this.rear_v = 0.0;
      }
      if (initObj.hasOwnProperty('rear_yaw')) {
        this.rear_yaw = initObj.rear_yaw
      }
      else {
        this.rear_yaw = 0.0;
      }
      if (initObj.hasOwnProperty('rear_speed')) {
        this.rear_speed = initObj.rear_speed
      }
      else {
        this.rear_speed = 0.0;
      }
      if (initObj.hasOwnProperty('rear_acceleration')) {
        this.rear_acceleration = initObj.rear_acceleration
      }
      else {
        this.rear_acceleration = 0.0;
      }
      if (initObj.hasOwnProperty('rear_distance')) {
        this.rear_distance = initObj.rear_distance
      }
      else {
        this.rear_distance = 0.0;
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
    // Serializes a message object of type CaccSensorPacket
    // Serialize message field [id]
    bufferOffset = _serializer.int16(obj.id, buffer, bufferOffset);
    // Serialize message field [manual]
    bufferOffset = _serializer.bool(obj.manual, buffer, bufferOffset);
    // Serialize message field [thw]
    bufferOffset = _serializer.float32(obj.thw, buffer, bufferOffset);
    // Serialize message field [alpha]
    bufferOffset = _serializer.float32(obj.alpha, buffer, bufferOffset);
    // Serialize message field [beta]
    bufferOffset = _serializer.float32(obj.beta, buffer, bufferOffset);
    // Serialize message field [sensor2frontbumper]
    bufferOffset = _serializer.float32(obj.sensor2frontbumper, buffer, bufferOffset);
    // Serialize message field [sensor2rearbumper]
    bufferOffset = _serializer.float32(obj.sensor2rearbumper, buffer, bufferOffset);
    // Serialize message field [vel_gain]
    bufferOffset = _serializer.int16(obj.vel_gain, buffer, bufferOffset);
    // Serialize message field [vel_gain_low]
    bufferOffset = _serializer.int16(obj.vel_gain_low, buffer, bufferOffset);
    // Serialize message field [vel_gain_dec]
    bufferOffset = _serializer.int16(obj.vel_gain_dec, buffer, bufferOffset);
    // Serialize message field [x]
    bufferOffset = _serializer.float32(obj.x, buffer, bufferOffset);
    // Serialize message field [y]
    bufferOffset = _serializer.float32(obj.y, buffer, bufferOffset);
    // Serialize message field [u]
    bufferOffset = _serializer.float32(obj.u, buffer, bufferOffset);
    // Serialize message field [v]
    bufferOffset = _serializer.float32(obj.v, buffer, bufferOffset);
    // Serialize message field [yaw]
    bufferOffset = _serializer.float32(obj.yaw, buffer, bufferOffset);
    // Serialize message field [speed]
    bufferOffset = _serializer.float32(obj.speed, buffer, bufferOffset);
    // Serialize message field [acceleration]
    bufferOffset = _serializer.float32(obj.acceleration, buffer, bufferOffset);
    // Serialize message field [front_x]
    bufferOffset = _serializer.float32(obj.front_x, buffer, bufferOffset);
    // Serialize message field [front_y]
    bufferOffset = _serializer.float32(obj.front_y, buffer, bufferOffset);
    // Serialize message field [front_u]
    bufferOffset = _serializer.float32(obj.front_u, buffer, bufferOffset);
    // Serialize message field [front_v]
    bufferOffset = _serializer.float32(obj.front_v, buffer, bufferOffset);
    // Serialize message field [front_yaw]
    bufferOffset = _serializer.float32(obj.front_yaw, buffer, bufferOffset);
    // Serialize message field [front_speed]
    bufferOffset = _serializer.float32(obj.front_speed, buffer, bufferOffset);
    // Serialize message field [front_acceleration]
    bufferOffset = _serializer.float32(obj.front_acceleration, buffer, bufferOffset);
    // Serialize message field [front_distance]
    bufferOffset = _serializer.float32(obj.front_distance, buffer, bufferOffset);
    // Serialize message field [rear_x]
    bufferOffset = _serializer.float32(obj.rear_x, buffer, bufferOffset);
    // Serialize message field [rear_y]
    bufferOffset = _serializer.float32(obj.rear_y, buffer, bufferOffset);
    // Serialize message field [rear_u]
    bufferOffset = _serializer.float32(obj.rear_u, buffer, bufferOffset);
    // Serialize message field [rear_v]
    bufferOffset = _serializer.float32(obj.rear_v, buffer, bufferOffset);
    // Serialize message field [rear_yaw]
    bufferOffset = _serializer.float32(obj.rear_yaw, buffer, bufferOffset);
    // Serialize message field [rear_speed]
    bufferOffset = _serializer.float32(obj.rear_speed, buffer, bufferOffset);
    // Serialize message field [rear_acceleration]
    bufferOffset = _serializer.float32(obj.rear_acceleration, buffer, bufferOffset);
    // Serialize message field [rear_distance]
    bufferOffset = _serializer.float32(obj.rear_distance, buffer, bufferOffset);
    // Serialize message field [checksum]
    bufferOffset = _serializer.uint32(obj.checksum, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type CaccSensorPacket
    let len;
    let data = new CaccSensorPacket(null);
    // Deserialize message field [id]
    data.id = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [manual]
    data.manual = _deserializer.bool(buffer, bufferOffset);
    // Deserialize message field [thw]
    data.thw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [alpha]
    data.alpha = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [beta]
    data.beta = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sensor2frontbumper]
    data.sensor2frontbumper = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [sensor2rearbumper]
    data.sensor2rearbumper = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vel_gain]
    data.vel_gain = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [vel_gain_low]
    data.vel_gain_low = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [vel_gain_dec]
    data.vel_gain_dec = _deserializer.int16(buffer, bufferOffset);
    // Deserialize message field [x]
    data.x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [y]
    data.y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [u]
    data.u = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [v]
    data.v = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yaw]
    data.yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [speed]
    data.speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [acceleration]
    data.acceleration = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_x]
    data.front_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_y]
    data.front_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_u]
    data.front_u = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_v]
    data.front_v = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_yaw]
    data.front_yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_speed]
    data.front_speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_acceleration]
    data.front_acceleration = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [front_distance]
    data.front_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_x]
    data.rear_x = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_y]
    data.rear_y = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_u]
    data.rear_u = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_v]
    data.rear_v = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_yaw]
    data.rear_yaw = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_speed]
    data.rear_speed = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_acceleration]
    data.rear_acceleration = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [rear_distance]
    data.rear_distance = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [checksum]
    data.checksum = _deserializer.uint32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 125;
  }

  static datatype() {
    // Returns string type for a message object
    return 'cacc_msgs/CaccSensorPacket';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '53f6fd0b756b85940b07ea746c26c901';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    #Header Header
    
    int16 id
    bool manual #1: manual. 0: automated
    float32 thw
    float32 alpha
    float32 beta
    float32 sensor2frontbumper
    float32 sensor2rearbumper
    int16 vel_gain
    int16 vel_gain_low
    int16 vel_gain_dec
    
    #ego car
    float32 x
    float32 y
    float32 u
    float32 v
    float32 yaw
    float32 speed
    float32 acceleration
    
    #front car
    float32 front_x
    float32 front_y
    float32 front_u
    float32 front_v
    float32 front_yaw
    float32 front_speed
    float32 front_acceleration
    float32 front_distance
    
    #rear car
    float32 rear_x
    float32 rear_y
    float32 rear_u
    float32 rear_v
    float32 rear_yaw
    float32 rear_speed
    float32 rear_acceleration
    float32 rear_distance
    
    uint32 checksum
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new CaccSensorPacket(null);
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

    if (msg.sensor2frontbumper !== undefined) {
      resolved.sensor2frontbumper = msg.sensor2frontbumper;
    }
    else {
      resolved.sensor2frontbumper = 0.0
    }

    if (msg.sensor2rearbumper !== undefined) {
      resolved.sensor2rearbumper = msg.sensor2rearbumper;
    }
    else {
      resolved.sensor2rearbumper = 0.0
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

    if (msg.x !== undefined) {
      resolved.x = msg.x;
    }
    else {
      resolved.x = 0.0
    }

    if (msg.y !== undefined) {
      resolved.y = msg.y;
    }
    else {
      resolved.y = 0.0
    }

    if (msg.u !== undefined) {
      resolved.u = msg.u;
    }
    else {
      resolved.u = 0.0
    }

    if (msg.v !== undefined) {
      resolved.v = msg.v;
    }
    else {
      resolved.v = 0.0
    }

    if (msg.yaw !== undefined) {
      resolved.yaw = msg.yaw;
    }
    else {
      resolved.yaw = 0.0
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

    if (msg.front_x !== undefined) {
      resolved.front_x = msg.front_x;
    }
    else {
      resolved.front_x = 0.0
    }

    if (msg.front_y !== undefined) {
      resolved.front_y = msg.front_y;
    }
    else {
      resolved.front_y = 0.0
    }

    if (msg.front_u !== undefined) {
      resolved.front_u = msg.front_u;
    }
    else {
      resolved.front_u = 0.0
    }

    if (msg.front_v !== undefined) {
      resolved.front_v = msg.front_v;
    }
    else {
      resolved.front_v = 0.0
    }

    if (msg.front_yaw !== undefined) {
      resolved.front_yaw = msg.front_yaw;
    }
    else {
      resolved.front_yaw = 0.0
    }

    if (msg.front_speed !== undefined) {
      resolved.front_speed = msg.front_speed;
    }
    else {
      resolved.front_speed = 0.0
    }

    if (msg.front_acceleration !== undefined) {
      resolved.front_acceleration = msg.front_acceleration;
    }
    else {
      resolved.front_acceleration = 0.0
    }

    if (msg.front_distance !== undefined) {
      resolved.front_distance = msg.front_distance;
    }
    else {
      resolved.front_distance = 0.0
    }

    if (msg.rear_x !== undefined) {
      resolved.rear_x = msg.rear_x;
    }
    else {
      resolved.rear_x = 0.0
    }

    if (msg.rear_y !== undefined) {
      resolved.rear_y = msg.rear_y;
    }
    else {
      resolved.rear_y = 0.0
    }

    if (msg.rear_u !== undefined) {
      resolved.rear_u = msg.rear_u;
    }
    else {
      resolved.rear_u = 0.0
    }

    if (msg.rear_v !== undefined) {
      resolved.rear_v = msg.rear_v;
    }
    else {
      resolved.rear_v = 0.0
    }

    if (msg.rear_yaw !== undefined) {
      resolved.rear_yaw = msg.rear_yaw;
    }
    else {
      resolved.rear_yaw = 0.0
    }

    if (msg.rear_speed !== undefined) {
      resolved.rear_speed = msg.rear_speed;
    }
    else {
      resolved.rear_speed = 0.0
    }

    if (msg.rear_acceleration !== undefined) {
      resolved.rear_acceleration = msg.rear_acceleration;
    }
    else {
      resolved.rear_acceleration = 0.0
    }

    if (msg.rear_distance !== undefined) {
      resolved.rear_distance = msg.rear_distance;
    }
    else {
      resolved.rear_distance = 0.0
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

module.exports = CaccSensorPacket;
