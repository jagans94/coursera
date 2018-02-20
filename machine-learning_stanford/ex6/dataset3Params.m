function [C, sigma] = dataset3Params(X, y, Xval, yval)
%DATASET3PARAMS returns your choice of C and sigma for Part 3 of the exercise
%where you select the optimal (C, sigma) learning parameters to use for SVM
%with RBF kernel
%   [C, sigma] = DATASET3PARAMS(X, y, Xval, yval) returns your choice of C and 
%   sigma. You should complete this function to return the optimal C and 
%   sigma based on a cross-validation set.
%
m = 100
% You need to return the following variables correctly.
C = .01;
sigma = 0.01;

% ====================== YOUR CODE HERE ======================
% Instructions: Fill in this function to return the optimal C and sigma
%               learning parameters found using the cross validation set.
%               You can use svmPredict to predict the labels on the cross
%               validation set. For example, 
%                   predictions = svmPredict(model, Xval);
%               will return the predictions on the cross validation set.
%
%  Note: You can compute the prediction error using 
%        mean(double(predictions ~= yval))
%

least_prediction_error = 1;
best_C = 0.01;
best_sigma = 0.01; 

for C_test = [0.01 0.03 0.1 0.3 1 3 10 30]
    for sigma_test = [0.01 0.03 0.1 0.3 1 3 10 30]
        model = svmTrain(X, y, C_test, @(x1, x2) gaussianKernel(x1, x2, sigma_test));
        predictions = svmPredict(model, Xval);
        prediction_error = mean(double(predictions ~= yval));

        if(prediction_error < least_prediction_error)
          least_prediction_error = prediction_error;
          best_C = C_test;
          best_sigma = sigma_test;
        endif;
        
    end
end

C = best_C;
sigma = best_sigma;
% =========================================================================

end
