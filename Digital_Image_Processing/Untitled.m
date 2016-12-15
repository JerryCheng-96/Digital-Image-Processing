I=imread('SSCplx.bmp');
INoise = imnoise(I, 'gaussian', 0, 0.001);
imshow(INoise);