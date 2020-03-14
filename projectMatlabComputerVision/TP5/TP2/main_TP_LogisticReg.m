% %------------------------------------
% %   LOGISTIC REGRESSION CLASSIFIER
% %------------------------------------
% clear
% clc
% close all
% 
% %% STEP 1: DESCRIPTION
% % Load the images and labels
% ArrayIm=[];
% ArrayImBi=[];
% ArrayImSup=[];
% string='PROJECT_Data/ISIC_0000';
% n=0;
% 
% nfirstimages=1000;
% 
% for i=0:nfirstimages
%     
%      j=int2str(i);
%      
%     if (i>-1 && i<10)
%         stringI1=strcat(string,'00',j,'.jpg');
%         stringI2=strcat(string,'00',j,'_segmentation.png');
%         stringI3=strcat(string,'00',j,'_superpixels.png');
%     elseif (i>9 && i<100)
%         stringI1=strcat(string,'0',j,'.jpg');
%         stringI2=strcat(string,'0',j,'_segmentation.png');
%         stringI3=strcat(string,'0',j,'_superpixels.png');
%     elseif (i>99 && i<1000)
%         stringI1=strcat(string,j,'.jpg');
%         stringI2=strcat(string,j,'_segmentation.png');
%         stringI3=strcat(string,j,'_superpixels.png');
%     end
%       
%     if (isfile(stringI1))
%         n=n+1
%         I1=imread(stringI1);
%         I2=imread(stringI2);
%         I3=imread(stringI3);
%         
%         ArrayIm{n}=I1;
%         ArrayImBi{n}=I2;
%         ArrayImSup{n}=I3;
%     end
% end
    


% Number of images
num_Im = length(ArrayIm);

% Number of features (in the case of ShapeFeat it is 10)
num_features = 200;

% Initialiation of matrix of descriptors. It will have a size (m x n), where
% m is the number of training patterns (i.e. elements) and n is the number 
% of features (i.e. the length of the feature vector which characterizes 
% the cutting edge).
X = zeros(num_Im, num_features);

% Describe the images of the horizontal edges by calling the fGetShapeFeat 
% function
for i=1:num_Im
    disp(['Describing image number ' num2str(i)]);
    
    % Compute the descriptors of the cutting edge usign the fGetShapeFeat
    % function
    desc_Im_i = fGetShapeFeat2(logical(ArrayImBi{i}));
    
    % Store the feature vector into the matrix X.
    X(i,:) = desc_Im_i;
end

% 
% Create the vector of labels Y. Y(j) will store the label of the curring
% edge represented by the feature vector contained in the j-th row of the 
% matrix X.
% The problem will be binary: class 0 correspond to a low or medium wear
% level, whereas class 1 correspond to a high wear level.

Y = csvread('tablefile.csv');
Y=Y(1:num_Im);
Y=Y';
%Y = labels(:,2)'>=2;

save('tool_descriptors.mat', 'X', 'Y');

%% STEP 2: CLASSIFICATION

%% PRELIMINARY: LOAD DATASET AND PARTITION TRAIN-TEST SETS (NO NEED TO CHANGE ANYTHING)

% clear
% clc
% close all

load tool_descriptors;
% X contains the training patterns (dimension 10)
% Y contains the class label of the patterns (i.e. Y(37) contains the label
% of the pattern X(37,:) ).

% Number of patterns (i.e., elements) and variables per pattern in this
% dataset
[num_patterns, num_features] = size(X);

% Normalization of the data
mu_data = mean(X);
std_data = std(X);
X = (X-mu_data)./std_data;

% Parameter that indicates the percentage of patterns that will be used for
% the training
p_train = 0.6;

% SPLIT DATA INTO TRAINING AND TEST SETS

num_patterns_train = round(p_train*num_patterns);

indx_permutation = randperm(num_patterns);

indxs_train = indx_permutation(1:num_patterns_train);
indxs_test = indx_permutation(num_patterns_train+1:end);

X_train = X(indxs_train, :);
Y_train = Y(indxs_train);

X_test= X(indxs_test, :);
Y_test = Y(indxs_test);


%% PART 2.1: TRAINING OF THE CLASSIFIER AND CLASSIFICATION OF THE TEST SET

% Learning rate. Change it accordingly, depending on how the cost function
% evolve along the iterations
alpha = 0.0000003;

% The function fTrain_LogisticReg implements the logistic regression 
% classifier. Open it and complete the code.

% TRAINING
theta = fTrain_LogisticReg(X_train, Y_train, alpha);

% CLASSIFICATION OF THE TEST SET
Y_test_hat = fClassify_LogisticReg(X_test, theta);

% Assignation of the class
Y_test_asig = Y_test_hat>=0.5;

%% PART 2.2: PERFORMANCE OF THE CLASSIFIER: CALCULATION OF THE ACCURACY AND FSCORE

% Show confusion matrix
figure;
plotconfusion(Y_test, Y_test_asig);


% ACCURACY AND F-SCORE
% ====================== YOUR CODE HERE ======================
TP=0;
TN=0;
FP=0;
FN=0;

for i=1:length(Y_test)
    if (Y_test(i)==0)
        if (Y_test_asig(i)==0)
            TP=TP+1;
        else
            FN=FN+1;
        end
    else
        if (Y_test_asig(i)==1)
            TN=TN+1;
        else
            FP=FP+1;
        end
    end
end

accuracy=(TP+TN)/(TP+TN+FP+FN);
precision=TP/(TP+FP);
recall=TP/(TP+FN);
FScore= 2 * (precision*recall)/(precision+recall);

[A,B,~]=roc(Y_test, Y_test_asig);
plot(A,B);

% ============================================================
% 
fprintf('\n******\nAccuracy = %1.4f%% (classification)\n', accuracy*100);
fprintf('\n******\nFScore = %1.4f (classification)\n', FScore);
