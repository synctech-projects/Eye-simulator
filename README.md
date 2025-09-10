**راه اندازی پروژه شبیه ساز چشم با استفاده از ماژول ESP32-C3 Super mini و نمایشگر Tft گرد 1.28 اینچ با چیپ GC9A01**

1-ابتدا هر سه فایل tools و Library و eye را دانلود کنید(روی فلش کنار گزینه Code که رنگ سبز دارد کلیک کنید و Download ZIP را بزنید تا دانلود شود).

2-سپس پوشه tools را داخل ادرس C:\Users\your system\Documents\Arduino قرار دهید.

3-بعد از ان،پوشه های داخل فایل Library را داخل ادرس C:\Users\your system\Documents\Arduino\libraries قرار دهید.

4-از پوشه eye فایل eye.ino را باز کنید،از منوی tools ابتدا برد LOLIN C3 Mini را انتخاب کنید،قسمت partition sheme را روی گزینه No OTA (1MB APP / 3MB SPIFFS) قرار دهید،در اخر پورت را تنظیم کنید،و گزینه ESP32 Sketch data upload را بزنید،پس از اپلو شدن فایل باینری data،حالا باید فایل ino را اپلود کنید،پس گزینه اپلود را بزنید و منتظر بمانید تا کامپایل و اپلود شود.

**نحوه سیم بندی :**

|**LCD**|**ESP32**|
|:-----:|:-----:|
|`VCC`|3.3V|
|`GND`|GND|
|`SCL`|GPIO 4|
|`SDA`|GPIO 6|
|`CS`|GPIO 7|
|`DC`|GPIO 10|
|`RST`|GPIO 9|
|`BL`|GPIO 3|
