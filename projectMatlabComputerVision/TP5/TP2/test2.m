%test2
O=ArrayIm{9};
imshow(O2);
O2=O(:,:,2);
h=histcounts(O2);
h=h(1:60);