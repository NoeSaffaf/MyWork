function shapeFeatVector = fGetShapeFeat2(region)
Circ=regionprops(region,'Circularity');
shapeFeatVector(1)=Circ.Circularity;
for i=1:200
    shapeFeatVector(i)=shapeFeatVector(1);
end

% 
% Ec = regionprops(region,'Eccentricity');
% shapeFeatVector(2)= Ec.Eccentricity;

% EX = regionprops(region,'Extent');
% shapeFeatVector(1)=EX.Extent;
% 
% rg=regionprops(region,'Perimeter');
% shapeFeatVector(4) = rg.Perimeter;
% 
% EquivDiameter = regionprops(region,'EquivDiameter');
% shapeFeatVector(1) = EquivDiameter.EquivDiameter;
% 
% Fa=regionprops(region,'FilledArea');
% shapeFeatVector(6) = Fa.FilledArea;
% 
% MAL=regionprops(region,'MinorAxisLength');
% shapeFeatVector(1) = MAL.MinorAxisLength;
% 
% MAL2=regionprops(region,'MajorAxisLength');
% shapeFeatVector(8) = MAL2.MajorAxisLength;
% 
% shapeFeatVector(9) = shapeFeatVector(8)/shapeFeatVector(7);
end