# Filter playground

This started as a tiny project where I wanted to implement the Kuwahara filter (shoutout to [Acerola](https://www.youtube.com/watch?v=LDhN-JK3U9g)) but it quickly became a funny thing to do. So maybe I'll implement some other filters for images. Currently, the available filters are:

- [Kuwahara Filter](https://en.wikipedia.org/wiki/Kuwahara_filter).
- [Ordered Dithering](https://en.wikipedia.org/wiki/Ordered_dithering).

I tried to make the filters as modular and easy to use as possible. Each filter is his own static class so you can apply the filter without an instance. For example:

```cpp
#include "kuwahara.hpp"
#include <opencv2/core/core.hpp">

int main(void) {
	cv::Mat inputImg = imread("your/image/path.ext", IMREAD_COLOR);
	cv::Mat output = Kuwahara::applyFilter(inputImg, 5);

	return 0;
}
```

## Disclaimer

I'm not that good at C++ nor OpenCV, so my implementations aren't as optimal as they could be. I make this for fun and for practice.

Hope you like it and you find this useful. If you use my code, please give me credit by linking to this repo or something.

## Bibliography

The majority of filters will be implemented using the Wikipedia page because sometimes the original papers are quite expensive for me.

- [Kuwahara Filter (Wikipedia)](https://en.wikipedia.org/wiki/Kuwahara_filter).
- [Ordered Dithering (Wikipedia)](https://en.wikipedia.org/wiki/Ordered_dithering).
- [Ordered Dithering (Computerphile)](https://www.youtube.com/watch?v=IviNO7iICTM).
