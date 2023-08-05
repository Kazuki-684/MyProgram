import pyocr
from PIL import Image, ImageEnhance
import os

def tesseractOCR(url):
    TESSERACT_PATH =  "/usr/local/lib/libtesseract.so.5"
    TESSDATA_PATH = "/usr/local/share/tessdata"
    
    os.environ["PATH"] += os.pathsep + TESSERACT_PATH
    os.environ["TESSDATA_PREFIX"] = TESSDATA_PATH
    
    tools = pyocr.get_available_tools()
    tool = tools[0]
    
    builder = pyocr.builders.TextBuilder(tesseract_layout=6)
    
    img = Image.open(url)
    
    img_g = img.convert('L')
    enhancer = ImageEnhance.Contrast(img_g)
    img_con = enhancer.enhance(2.0)
    
    txt_pyocr = tool.image_to_string(img_con, lang='jpn', builder=builder)
    
    txt_pyocr = txt_pyocr.replace(' ','')
    txt_pyocr = txt_pyocr.replace('\n','')
    
    return txt_pyocr