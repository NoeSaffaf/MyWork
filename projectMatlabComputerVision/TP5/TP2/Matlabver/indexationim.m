function B=indexationim(I)
[a,b]=size(I);
B=zeros(a,b);
matref=[1,2,4;
        8,0,16;
        32,64,128];
    
for i=2:a-1
    for j=2:b-1
        sousmat=I(i-1:i+1 , j-1:j+1);
        sousmat=(sousmat>=I(i,j));
        T=sousmat.*matref;
        index=sum(T(:));
        B(i,j)=index;
    end
end