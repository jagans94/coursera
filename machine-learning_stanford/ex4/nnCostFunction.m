function [J grad d3 ] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)

Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));
Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));


m = size(X, 1);
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% Forward Propagation

% Expand the 'y' output values into a matrix of single values
y_matrix = eye(num_labels)(y,:);

% Resizing X to include bias 
a1 = [ones(m,1) X];

% Calculating the output of 2nd/Hidden Layer
z2 = a1*Theta1'; a2 = sigmoid(z2);

% Resizing 2nd Layer to include bias 
a2 = [ones(size(a2,1),1) a2];

% Calculating the output of the 3rd/Output Layer, i.e. h(x) 
z3 = a2*Theta2'; a3 = sigmoid(z3);

% Cost Function (Normal) 
J_normal = sum(sum(y_matrix.*log(a3) + (1-y_matrix).*log(1 - a3)))*(-1/m);

% Calculating Summation of Theta^2. 
% Could be done in a single line, but that would be damn confusing.
% Note: Including the bias unit doesn't seem to change the regularization output by much. %Why is that?
Theta1(:,1) = 0;
Theta2(:,1) = 0;

% Applying element-wise squaring and summation.
T1sq_sum = sum(Theta1(:).^2);
T2sq_sum = sum(Theta2(:).^2);
 
% Cost Function (Regularization)  
J_reg = (lambda/(2*m))*(T1sq_sum + T2sq_sum);

J = J_normal + J_reg;

% Backward Propagation
% Why are we not scaling d3 with sigmoidGradient(z3)?
d3 = (a3-y_matrix);
d2 = (d3*Theta2(:,2:size(Theta2,2))).*sigmoidGradient(z2);

Theta1_grad = (1/m)*(d2'*a1) +   (lambda/m)*(Theta1);
Theta2_grad = (1/m)*(d3'*a2) + (lambda/m)*(Theta2);

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];

end

