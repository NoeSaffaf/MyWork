%test

 I1=ArrayImBi{100};
 a=regionprops(I1,'Centroid');
 xyCentroids = vertcat(a.Centroid);
 x = round(xyCentroids(:, 1));
 y = round(xyCentroids(:, 2));
 x=x(255);
 y=y(255);
 [A,B]=size(I1);
 A=round(A/2);
 B=round(B/2);

 
 I2=imtranslate(I1,[x-A,y-B]);
 imshowpair(I1,I2,'montage');
