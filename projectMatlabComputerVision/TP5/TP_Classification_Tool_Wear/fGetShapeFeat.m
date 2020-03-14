function shapeFeatVector = fGetShapeFeat(region)
% This function gets the shapeFeat descriptors from a binary region
%
% INPUT
%   - region: Image with a binary region to get the descriptors from. There
%   is ONLY ONE REGION IN THE IMAGE. The type of the image must be LOGICAL
%
% OUTPUT
%   shapeFeatVector: Vector with all the descriptors of the ShapeFeat.
%   These are:
%     � Convex Area: Number of pixels of the smallest convex polygon that
%     contains the region.
%     � Eccentricity: Scalar that specifies the eccentricity of the ellipse 
%     that has the same second central moments as the region. 
%     � Perimeter: Number of points in the contour of the region.
%     � Equivalent Diameter: Scalar that specifies the diameter of a circle
%      with the same area as the region.
%     � Extent: Scalar that specifies the ratio of the pixels of the
%     region to the pixels in the bounding box around the region.
%     � Filled Area: Number of pixels belonging to the region after filling
%     its possible holes.
%     � Minor Axis Length: Length of the minor axis of the ellipse that has
%     the same second central moments as the region. 
%     � Major Axis Length: Length of the major axis of the ellipse that has
%     the same second central moments as the region.
%     � R: Ratio between the major and minor axis of the ellipse that has
%     the same second central moments as the region.
%     � Solidity: Ratio between the area of the region and the Convex Area
%     of the region.

% Initialise the output
shapeFeatVector = zeros(1,10);

% Look at the Matlab's regionprops function to get the properties of the
% region that you need to get the descriptors of ShapeFeats (mentioned
% above)
% ====================== YOUR CODE HERE ======================



% ============================================================

% Convex Area: Number of pixels of the smallest convex polygon that
% contains the region.
% ====================== YOUR CODE HERE ======================

CA = regionprops(region,'ConvexArea');
shapeFeatVector(1)=CA.ConvexArea;
% ============================================================

% Eccentricity: Scalar that specifies the eccentricity of the ellipse that
% has the same second central moments as the region.
% ====================== YOUR CODE HERE ======================
Ec = regionprops(region,'Eccentricity');
shapeFeatVector(2)= Ec.Eccentricity;
% ============================================================

% Perimeter: Number of points in the contour of the region.
% ====================== YOUR CODE HERE ======================
rg=regionprops(region,'Perimeter');
shapeFeatVector(3) = rg.Perimeter;
% ============================================================

% Equivalent Diameter: Scalar that specifies the diameter of a circle with
% the same area as the region.
% ====================== YOUR CODE HERE ======================
area = regionprops(region,'Area');
shapeFeatVector(4) = sqrt(4*area.Area/pi);
% ============================================================

% Extent: Scalar that specifies the ratio of the pixels of the region to
% the pixels in the bounding box around the region.
% ====================== YOUR CODE HERE ======================
EX = regionprops(region,'Extent');
shapeFeatVector(5)=EX.Extent;
% ============================================================

% Filled Area: Number of pixels belonging to the region after filling its
% possible holes.
% ====================== YOUR CODE HERE ======================
Fa=regionprops(region,'FilledArea');
shapeFeatVector(6) = Fa.FilledArea;
% ============================================================

% Minor Axis Length: Length of the minor axis of the ellipse that has the
% same second central moments as the region.
% ====================== YOUR CODE HERE ======================
MAL=regionprops(region,'MinorAxisLength');
shapeFeatVector(7) = MAL.MinorAxisLength;
% ============================================================

% Major Axis Length: Length of the major axis of the ellipse that has the
% same second central moments as the region.
% ====================== YOUR CODE HERE ======================
MAL2=regionprops(region,'MajorAxisLength');
shapeFeatVector(8) = MAL2.MajorAxisLength;
% ============================================================

% R: Ratio between the major and minor axis of the ellipse that has the
% same second central moments as the region.
% ====================== YOUR CODE HERE ======================
shapeFeatVector(9) = shapeFeatVector(8)/shapeFeatVector(7);
% ============================================================

% Solidity: Ratio between the area of the region and the Convex Area of the
% region.
% ====================== YOUR CODE HERE ======================
shapeFeatVector(10) = area.Area/shapeFeatVector(1);
% ============================================================
end