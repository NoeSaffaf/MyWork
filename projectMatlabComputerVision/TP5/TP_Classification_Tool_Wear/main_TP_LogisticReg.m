%------------------------------------
%   LOGISTIC REGRESSION CLASSIFIER
%------------------------------------
clear
clc
close all

%% STEP 1: DESCRIPTION
% Load the images and labels
load Horizontal_edges;
% Number of images of cutting edges
num_edges = length(horiz_edges);

% Number of features (in the case of ShapeFeat it is 10)
num_features = 10;

% Initialiation of matrix of descriptors. It will have a size (m x n), where
% m is the number of training patterns (i.e. elements) and n is the number 
% of features (i.e. the length of the feature vector which characterizes 
% the cutting edge).
X = zeros(num_edges, num_features);

% Describe the images of the horizontal edges by calling the fGetShapeFeat 
% function
for i=1:num_edges
    disp(['Describing image number ' num2str(i)]);
    
    % Get the i-th cutting edge
    edge = logical(horiz_edges{i}); % DON'T REMOVE
    
    % Compute the descriptors of the cutting edge usign the fGetShapeFeat
    % function
    desc_edge_i = fGetShapeFeat(edge);
    
    % Store the feature vector into the matrix X.
    X(i,:) = desc_edge_i;
end

% Create the vector of labels Y. Y(j) will store the label of the curring
% edge represented by the feature vector contained in the j-th row of the 
% matrix X.
% The problem will be binary: class 0 correspond to a low or medium wear
% level, whereas class 1 correspond to a high wear level.
Y = labels(:,2)'>=2;

save('tool_descriptors.mat', 'X', 'Y');

%% STEP 2: CLASSIFICATION

%% PRELIMINARY: LOAD DATASET AND PARTITION TRAIN-TEST SETS (NO NEED TO CHANGE ANYTHING)

clear
clc
close all

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
p_train = 0.7;

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
alpha = 0.00001;

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
