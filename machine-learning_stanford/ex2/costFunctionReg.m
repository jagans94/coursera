function [J, grad] = costFunctionReg(theta, X, y, lambda)
%COSTFUNCTIONREG Compute cost and gradient for logistic regression with regularization
%   J = COSTFUNCTIONREG(theta, X, y, lambda) computes the cost of using
%   theta as the parameter for regularized logistic regression and the
%   gradient of the cost w.r.t. to the parameters. 

% Initialize some useful values
m = length(y); % number of training examples

% You need to return the following variables correctly 
J = 0;
n=length(theta);
grad = zeros(n);
% ====================== YOUR CODE HERE ======================
% Instructions: Compute the cost of a particular choice of theta.
%               You should set J to the cost.
%               Compute the partial derivatives and set grad to the partial
%               derivatives of the cost w.r.t. each parameter in theta


z=X*theta;
t=theta(1);

cost = -(y'*log(sigmoid(z)) + (1-y)'*log(1-sigmoid(z)));

J_normal_exp = (1/m)*cost;
g_normal_exp = (1/m)*(X'*(sigmoid(z) - y));

theta(1) = 0;

J_reg_exp = (lambda/(2*m))*(theta'*theta);
g_reg_exp = (lambda/m)*(theta);

J=J_normal_exp+J_reg_exp;
%gradient and not gradient descent
grad = g_normal_exp+g_reg_exp;

theta(1)=t;

% =============================================================

end
