# This Python file uses the following encoding: utf-8
"""autogenerated by genpy from cacc_msgs/CaccStatePacket.msg. Do not edit."""
import codecs
import sys
python3 = True if sys.hexversion > 0x03000000 else False
import genpy
import struct


class CaccStatePacket(genpy.Message):
  _md5sum = "d1e7f03c3be6f5504cfdc21bdc1d3462"
  _type = "cacc_msgs/CaccStatePacket"
  _has_header = False  # flag to mark the presence of a Header object
  _full_text = """int16 id
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
float32 acceleration"""
  __slots__ = ['id','manual','activated','thw','alpha','beta','vel_gain','vel_gain_low','vel_gain_dec','distance','speed','acceleration']
  _slot_types = ['int16','bool','bool','float32','float32','float32','int16','int16','int16','float32','float32','float32']

  def __init__(self, *args, **kwds):
    """
    Constructor. Any message fields that are implicitly/explicitly
    set to None will be assigned a default value. The recommend
    use is keyword arguments as this is more robust to future message
    changes.  You cannot mix in-order arguments and keyword arguments.

    The available fields are:
       id,manual,activated,thw,alpha,beta,vel_gain,vel_gain_low,vel_gain_dec,distance,speed,acceleration

    :param args: complete set of field values, in .msg order
    :param kwds: use keyword arguments corresponding to message field names
    to set specific fields.
    """
    if args or kwds:
      super(CaccStatePacket, self).__init__(*args, **kwds)
      # message fields cannot be None, assign default values for those that are
      if self.id is None:
        self.id = 0
      if self.manual is None:
        self.manual = False
      if self.activated is None:
        self.activated = False
      if self.thw is None:
        self.thw = 0.
      if self.alpha is None:
        self.alpha = 0.
      if self.beta is None:
        self.beta = 0.
      if self.vel_gain is None:
        self.vel_gain = 0
      if self.vel_gain_low is None:
        self.vel_gain_low = 0
      if self.vel_gain_dec is None:
        self.vel_gain_dec = 0
      if self.distance is None:
        self.distance = 0.
      if self.speed is None:
        self.speed = 0.
      if self.acceleration is None:
        self.acceleration = 0.
    else:
      self.id = 0
      self.manual = False
      self.activated = False
      self.thw = 0.
      self.alpha = 0.
      self.beta = 0.
      self.vel_gain = 0
      self.vel_gain_low = 0
      self.vel_gain_dec = 0
      self.distance = 0.
      self.speed = 0.
      self.acceleration = 0.

  def _get_types(self):
    """
    internal API method
    """
    return self._slot_types

  def serialize(self, buff):
    """
    serialize message into buffer
    :param buff: buffer, ``StringIO``
    """
    try:
      _x = self
      buff.write(_get_struct_h2B3f3h3f().pack(_x.id, _x.manual, _x.activated, _x.thw, _x.alpha, _x.beta, _x.vel_gain, _x.vel_gain_low, _x.vel_gain_dec, _x.distance, _x.speed, _x.acceleration))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize(self, str):
    """
    unpack serialized message in str into this message instance
    :param str: byte array of serialized message, ``str``
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 34
      (_x.id, _x.manual, _x.activated, _x.thw, _x.alpha, _x.beta, _x.vel_gain, _x.vel_gain_low, _x.vel_gain_dec, _x.distance, _x.speed, _x.acceleration,) = _get_struct_h2B3f3h3f().unpack(str[start:end])
      self.manual = bool(self.manual)
      self.activated = bool(self.activated)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill


  def serialize_numpy(self, buff, numpy):
    """
    serialize message with numpy array types into buffer
    :param buff: buffer, ``StringIO``
    :param numpy: numpy python module
    """
    try:
      _x = self
      buff.write(_get_struct_h2B3f3h3f().pack(_x.id, _x.manual, _x.activated, _x.thw, _x.alpha, _x.beta, _x.vel_gain, _x.vel_gain_low, _x.vel_gain_dec, _x.distance, _x.speed, _x.acceleration))
    except struct.error as se: self._check_types(struct.error("%s: '%s' when writing '%s'" % (type(se), str(se), str(locals().get('_x', self)))))
    except TypeError as te: self._check_types(ValueError("%s: '%s' when writing '%s'" % (type(te), str(te), str(locals().get('_x', self)))))

  def deserialize_numpy(self, str, numpy):
    """
    unpack serialized message in str into this message instance using numpy for array types
    :param str: byte array of serialized message, ``str``
    :param numpy: numpy python module
    """
    codecs.lookup_error("rosmsg").msg_type = self._type
    try:
      end = 0
      _x = self
      start = end
      end += 34
      (_x.id, _x.manual, _x.activated, _x.thw, _x.alpha, _x.beta, _x.vel_gain, _x.vel_gain_low, _x.vel_gain_dec, _x.distance, _x.speed, _x.acceleration,) = _get_struct_h2B3f3h3f().unpack(str[start:end])
      self.manual = bool(self.manual)
      self.activated = bool(self.activated)
      return self
    except struct.error as e:
      raise genpy.DeserializationError(e)  # most likely buffer underfill

_struct_I = genpy.struct_I
def _get_struct_I():
    global _struct_I
    return _struct_I
_struct_h2B3f3h3f = None
def _get_struct_h2B3f3h3f():
    global _struct_h2B3f3h3f
    if _struct_h2B3f3h3f is None:
        _struct_h2B3f3h3f = struct.Struct("<h2B3f3h3f")
    return _struct_h2B3f3h3f