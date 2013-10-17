% Intrinsic and Extrinsic Camera Parameters
%
% This script file can be directly excecuted under Matlab to recover the camera intrinsic and extrinsic parameters.
% IMPORTANT: This file contains neither the structure of the calibration objects nor the image coordinates of the calibration points.
%            All those complementary variables are saved in the complete matlab data file Calib_Results.mat.
% For more information regarding the calibration model visit http://www.vision.caltech.edu/bouguetj/calib_doc/


%-- Focal length:
fc = [ 578.178058429585462 ; 576.658983508326401 ];

%-- Principal point:
cc = [ 308.075751363667166 ; 162.102736172025033 ];

%-- Skew coefficient:
alpha_c = 0.000000000000000;

%-- Distortion coefficients:
kc = [ -0.531715142443432 ; 0.339430865344589 ; 0.006043707165226 ; 0.003852899067116 ; 0.000000000000000 ];

%-- Focal length uncertainty:
fc_error = [ 2.593715083550049 ; 2.773895559304200 ];

%-- Principal point uncertainty:
cc_error = [ 6.777691632957766 ; 4.885594299643569 ];

%-- Skew coefficient uncertainty:
alpha_c_error = 0.000000000000000;

%-- Distortion coefficients uncertainty:
kc_error = [ 0.018256871854740 ; 0.064364661858938 ; 0.002798986602912 ; 0.002092630415288 ; 0.000000000000000 ];

%-- Image size:
nx = 640;
ny = 368;


%-- Various other variables (may be ignored if you do not use the Matlab Calibration Toolbox):
%-- Those variables are used to control which intrinsic parameters should be optimized

n_ima = 17;						% Number of calibration images
est_fc = [ 1 ; 1 ];					% Estimation indicator of the two focal variables
est_aspect_ratio = 1;				% Estimation indicator of the aspect ratio fc(2)/fc(1)
center_optim = 1;					% Estimation indicator of the principal point
est_alpha = 0;						% Estimation indicator of the skew coefficient
est_dist = [ 1 ; 1 ; 1 ; 1 ; 0 ];	% Estimation indicator of the distortion coefficients


%-- Extrinsic parameters:
%-- The rotation (omc_kk) and the translation (Tc_kk) vectors for every calibration image and their uncertainties

%-- Image #1:
omc_1 = [ 1.918866e+00 ; 1.528632e-01 ; -1.293646e-01 ];
Tc_1  = [ -9.164495e+01 ; 4.227292e+01 ; 2.892825e+02 ];
omc_error_1 = [ 8.487340e-03 ; 7.762375e-03 ; 1.192888e-02 ];
Tc_error_1  = [ 3.425840e+00 ; 2.509784e+00 ; 1.821044e+00 ];

%-- Image #2:
omc_2 = [ 1.931471e+00 ; 3.363692e-01 ; -2.892447e-01 ];
Tc_2  = [ -1.216307e+02 ; 3.582231e+01 ; 3.214167e+02 ];
omc_error_2 = [ 8.426735e-03 ; 7.868032e-03 ; 1.205106e-02 ];
Tc_error_2  = [ 3.798266e+00 ; 2.792933e+00 ; 2.069636e+00 ];

%-- Image #3:
omc_3 = [ 1.851625e+00 ; 1.213327e+00 ; -6.804515e-01 ];
Tc_3  = [ -9.669629e+01 ; -3.924913e+01 ; 4.476347e+02 ];
omc_error_3 = [ 7.556844e-03 ; 9.264273e-03 ; 1.281928e-02 ];
Tc_error_3  = [ 5.273085e+00 ; 3.789321e+00 ; 2.233875e+00 ];

%-- Image #4:
omc_4 = [ 2.156566e+00 ; 3.015456e-02 ; -1.004842e-01 ];
Tc_4  = [ -1.072497e+02 ; 6.733300e+01 ; 3.344925e+02 ];
omc_error_4 = [ 8.722468e-03 ; 6.658899e-03 ; 1.361947e-02 ];
Tc_error_4  = [ 3.975459e+00 ; 2.936341e+00 ; 2.179244e+00 ];

%-- Image #5:
omc_5 = [ 1.446129e+00 ; 1.529914e+00 ; -9.644690e-01 ];
Tc_5  = [ -4.943209e+01 ; -2.718242e+01 ; 4.422407e+02 ];
omc_error_5 = [ 6.742381e-03 ; 1.036826e-02 ; 1.151866e-02 ];
Tc_error_5  = [ 5.184044e+00 ; 3.737757e+00 ; 1.743596e+00 ];

%-- Image #6:
omc_6 = [ 1.959279e+00 ; 6.979114e-02 ; -8.393655e-02 ];
Tc_6  = [ -9.685166e+01 ; 6.254776e+01 ; 2.633319e+02 ];
omc_error_6 = [ 8.409144e-03 ; 7.274750e-03 ; 1.215356e-02 ];
Tc_error_6  = [ 3.150490e+00 ; 2.331199e+00 ; 1.796973e+00 ];

%-- Image #7:
omc_7 = [ 2.292697e+00 ; -2.278209e-02 ; -1.674080e-02 ];
Tc_7  = [ -9.404613e+01 ; 6.176648e+01 ; 2.656212e+02 ];
omc_error_7 = [ 8.585486e-03 ; 5.936136e-03 ; 1.432959e-02 ];
Tc_error_7  = [ 3.166709e+00 ; 2.342739e+00 ; 1.830227e+00 ];

%-- Image #8:
omc_8 = [ 2.122806e+00 ; 9.051903e-01 ; -4.635880e-01 ];
Tc_8  = [ -1.028460e+02 ; -8.365478e+00 ; 3.562042e+02 ];
omc_error_8 = [ 8.166684e-03 ; 8.180394e-03 ; 1.388614e-02 ];
Tc_error_8  = [ 4.204621e+00 ; 3.028809e+00 ; 2.129538e+00 ];

%-- Image #9:
omc_9 = [ 1.607771e+00 ; 1.770494e+00 ; -9.991620e-01 ];
Tc_9  = [ -3.373352e+01 ; -5.561936e+01 ; 4.715922e+02 ];
omc_error_9 = [ 6.161322e-03 ; 1.041235e-02 ; 1.329660e-02 ];
Tc_error_9  = [ 5.539971e+00 ; 3.977831e+00 ; 1.989417e+00 ];

%-- Image #10:
omc_10 = [ -1.756812e+00 ; -1.707572e+00 ; -9.052615e-01 ];
Tc_10  = [ -9.411404e+01 ; -2.037321e+01 ; 2.249142e+02 ];
omc_error_10 = [ 6.801417e-03 ; 9.913383e-03 ; 1.364255e-02 ];
Tc_error_10  = [ 2.653681e+00 ; 1.976222e+00 ; 1.823890e+00 ];

%-- Image #11:
omc_11 = [ -7.890826e-01 ; -2.573321e+00 ; -1.338966e+00 ];
Tc_11  = [ -5.652505e+00 ; -5.472833e+01 ; 2.959894e+02 ];
omc_error_11 = [ 7.018902e-03 ; 1.200508e-02 ; 1.413111e-02 ];
Tc_error_11  = [ 3.502368e+00 ; 2.521674e+00 ; 2.206120e+00 ];

%-- Image #12:
omc_12 = [ -2.149995e+00 ; -2.170997e+00 ; 3.923255e-01 ];
Tc_12  = [ -8.512453e+01 ; -6.845449e+01 ; 3.573680e+02 ];
omc_error_12 = [ 9.666129e-03 ; 8.651390e-03 ; 1.772261e-02 ];
Tc_error_12  = [ 4.222682e+00 ; 3.007967e+00 ; 2.066461e+00 ];

%-- Image #13:
omc_13 = [ -2.284572e-02 ; -2.456860e+00 ; 1.994903e-01 ];
Tc_13  = [ 1.125037e+02 ; -6.931007e+01 ; 3.500383e+02 ];
omc_error_13 = [ 4.176298e-03 ; 1.264725e-02 ; 1.251199e-02 ];
Tc_error_13  = [ 4.167216e+00 ; 3.018216e+00 ; 2.873324e+00 ];

%-- Image #14:
omc_14 = [ 2.004630e+00 ; 2.065702e+00 ; -2.178567e-02 ];
Tc_14  = [ -4.431818e+01 ; -7.021504e+01 ; 3.855153e+02 ];
omc_error_14 = [ 9.276603e-03 ; 9.577406e-03 ; 1.772527e-02 ];
Tc_error_14  = [ 4.545297e+00 ; 3.246752e+00 ; 2.458044e+00 ];

%-- Image #15:
omc_15 = [ 2.005586e+00 ; 2.070390e+00 ; -5.274890e-04 ];
Tc_15  = [ -4.288810e+01 ; -7.153266e+01 ; 3.814657e+02 ];
omc_error_15 = [ 9.325590e-03 ; 9.539499e-03 ; 1.764967e-02 ];
Tc_error_15  = [ 4.499337e+00 ; 3.214172e+00 ; 2.445279e+00 ];

%-- Image #16:
omc_16 = [ 2.007299e+00 ; 2.069950e+00 ; -9.749049e-03 ];
Tc_16  = [ -4.353120e+01 ; -7.120554e+01 ; 3.837031e+02 ];
omc_error_16 = [ 9.324150e-03 ; 9.571712e-03 ; 1.773645e-02 ];
Tc_error_16  = [ 4.525191e+00 ; 3.232508e+00 ; 2.455701e+00 ];

%-- Image #17:
omc_17 = [ 1.917885e+00 ; 2.063643e+00 ; 7.948324e-02 ];
Tc_17  = [ 1.701029e+01 ; -6.903709e+01 ; 3.805616e+02 ];
omc_error_17 = [ 9.512962e-03 ; 9.197610e-03 ; 1.690420e-02 ];
Tc_error_17  = [ 4.494983e+00 ; 3.209288e+00 ; 2.519321e+00 ];

