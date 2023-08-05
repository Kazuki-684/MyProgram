import os
import ctypes

lang = "jpn"
filename = "/home/ubuntu/environment/forocr/test1.png"
libname = "/usr/local/lib/libtesseract.so.5"
TESSDATA_PREFIX = os.environ.get('TESSDATA_PREFIX')
if not TESSDATA_PREFIX:
    TESSDATA_PREFIX = "../"
    
print ("hello")

tesseract = ctypes.cdll.LoadLibrary(libname)
tesseract.TessVersion.restype = ctypes.c_char_p
tesseract_version = tesseract.TessVersion()
api = tesseract.TessBaseAPICreate()
print("hello5")
rc = tesseract.TessBaseAPIInit3(api, TESSDATA_PREFIX, lang)
print("hello4")
if (rc):
    print("hello3")
    tesseract.TessBaseAPIDelete(api)
    print("Could not initialize tesseract.\n")
    exit(3)

print("hello2")
text_out = tesseract.TessBaseAPIProcessPages(api, filename, None, 0)
result_text = ctypes.string_at(text_out)

print ('Tesseract-ocr version')
print (tesseract_version)
print (result_text)

