function LBPfilter=LBPfunction(I,V)

I=double(I(:,:,2));
B=indexationim(I);
[a,b]=size(B);
B=B(2:a-1,2:b-1);
LBP = histcounts(B,256,'Normalization','Probability');
[~,b2]=size(V);
for i=1:b2
    LBPfilter(i)=LBP(V(i));
end




%
% for i=1:4    
%     I=double(imread(strcat('images/Sand.',int2str(i),'.bmp')));
%     I=(I(:,:,1)+I(:,:,2)+I(:,:,3))/3;
%     B=indexationim(I);
%     [a,b]=size(B);
%     B=B(2:a-1,2:b-1);
%     %imshow(B,[]);
%     h = histcounts(B,256,'Normalization','Probability');
%     listehist2=[listehist2;h];
% end
% 
% for i=1:4    
%     I=double(imread(strcat('images/Terrain.',int2str(i),'.bmp')));
%     I=(I(:,:,1)+I(:,:,2)+I(:,:,3))/3;
%     B=indexationim(I);
%     [a,b]=size(B);
%     B=B(2:a-1,2:b-1);
%     %imshow(B,[]);
%     h = histcounts(B,256,'Normalization','Probability');
%     listehist3=[listehist3;h];
% end
% 
% plot(listehist1(2,:));
% hold on
% plot(listehist2(2,:));
% hold on
% plot(listehist3(2,:));
% legend('metal','sand','terrain');