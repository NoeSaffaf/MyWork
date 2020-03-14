%test
I=ArrayIm{1};
I1=double(I(:,:,2));
B=indexationim(I1);
[a,b]=size(B);
B=B(2:a-1,2:b-1);
LBP = histcounts(B,256,'Normalization','Probability');
plot(LBP);
hold on

V=find(LBP>0.0001);
save('ValeurLBPpertinantes.mat', 'V');