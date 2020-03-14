%test2

I1=ArrayImSup{1};
I2=ArrayImSup{2};
imshowpair(I1,I2,'montage');

I1=I1(:,:,1);
I=I1;
[a,b]=size(I);
h=histcounts(I1);
% plot(h);

taille=size(h);

for i=1:taille
    for j=1:a
        for k=1:b
            if I1(j,k)==h(i);
                I(j,k)=1;
            else
                I(j,k)=0;
            end
        end
    end
    imshow(I);
end