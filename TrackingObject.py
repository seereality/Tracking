# This file was automatically generated by SWIG (http://www.swig.org).
# Version 2.0.11
#
# Do not make changes to this file unless you know what you are doing--modify
# the SWIG interface file instead.





from sys import version_info
if version_info >= (2,6,0):
    def swig_import_helper():
        from os.path import dirname
        import imp
        fp = None
        try:
            fp, pathname, description = imp.find_module('_TrackingObject', [dirname(__file__)])
        except ImportError:
            import _TrackingObject
            return _TrackingObject
        if fp is not None:
            try:
                _mod = imp.load_module('_TrackingObject', fp, pathname, description)
            finally:
                fp.close()
            return _mod
    _TrackingObject = swig_import_helper()
    del swig_import_helper
else:
    import _TrackingObject
del version_info
try:
    _swig_property = property
except NameError:
    pass # Python < 2.2 doesn't have 'property'.
def _swig_setattr_nondynamic(self,class_type,name,value,static=1):
    if (name == "thisown"): return self.this.own(value)
    if (name == "this"):
        if type(value).__name__ == 'SwigPyObject':
            self.__dict__[name] = value
            return
    method = class_type.__swig_setmethods__.get(name,None)
    if method: return method(self,value)
    if (not static):
        self.__dict__[name] = value
    else:
        raise AttributeError("You cannot add attributes to %s" % self)

def _swig_setattr(self,class_type,name,value):
    return _swig_setattr_nondynamic(self,class_type,name,value,0)

def _swig_getattr(self,class_type,name):
    if (name == "thisown"): return self.this.own()
    method = class_type.__swig_getmethods__.get(name,None)
    if method: return method(self)
    raise AttributeError(name)

def _swig_repr(self):
    try: strthis = "proxy of " + self.this.__repr__()
    except: strthis = ""
    return "<%s.%s; %s >" % (self.__class__.__module__, self.__class__.__name__, strthis,)

try:
    _object = object
    _newclass = 1
except AttributeError:
    class _object : pass
    _newclass = 0



def mouse_click(*args):
  return _TrackingObject.mouse_click(*args)
mouse_click = _TrackingObject.mouse_click

def mousemove(*args):
  return _TrackingObject.mousemove(*args)
mousemove = _TrackingObject.mousemove

def getCentroid(*args):
  return _TrackingObject.getCentroid(*args)
getCentroid = _TrackingObject.getCentroid

def HSV_threshold(*args):
  return _TrackingObject.HSV_threshold(*args)
HSV_threshold = _TrackingObject.HSV_threshold

def Canny_Filter(*args):
  return _TrackingObject.Canny_Filter(*args)
Canny_Filter = _TrackingObject.Canny_Filter

def main(*args):
  return _TrackingObject.main(*args)
main = _TrackingObject.main
# This file is compatible with both classic and new-style classes.

cvar = _TrackingObject.cvar

