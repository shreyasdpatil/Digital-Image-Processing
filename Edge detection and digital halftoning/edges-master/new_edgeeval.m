% Demo for Structured Edge Detector (please see readme.txt first).

%% set opts for training (see edgesTrain.m)
opts=edgesTrain();                % default options (good settings)
opts.modelDir='models/';          % model will be in models/forest
opts.modelFnm='modelBsds';        % model name
opts.nPos=5e5; opts.nNeg=5e5;     % decrease to speedup training
opts.useParfor=0;                 % parallelize if sufficient memory

%% train edge detector (~20m/8Gb per tree, proportional to nPos/nNeg)
tic, model=edgesTrain(opts); toc; % will load model if already trained

%% set detection parameters (can set after training)
model.opts.multiscale=0;          % for top accuracy set multiscale=1
model.opts.sharpen=2;             % for top speed set sharpen=0
model.opts.nTreesEval=4;          % for top speed set nTreesEval=1
model.opts.nThreads=4;            % max number threads for evaluation
model.opts.nms=0;                 % set to true to enable nms

%% evaluate edge detector on BSDS500 (see edgesEval.m)
if(0), edgesEval( model, 'show',1, 'name','' ); end

%% detect edge and visualize results
I = imread('Pig.jpg');
tic, E=edgesDetect(I,model); toc
P = 1-E;
dim = size(P);
for i=1:dim(1)
    for j=1:dim(2)
        if P(i,j)>0.85
            P(i,j) = 255;
        else
            P(i,j) = 0;
        end
    end
end
        
figure(1); im(I); 
figure(2); im(1-E);
imwrite(1-E, 'Pig_Probability_map.jpg');
figure(3); im(P);
imwrite(P, 'Pig_binary_map.jpg');

%% Evaluating for ground truth 1
cell = load('Pig.mat');
cell = cell.groundTruth;
threshold = 10;
Precision = zeros(threshold, 5);
Recall = zeros(threshold, 5);
mean_precision = zeros(5, 1);
mean_recall = zeros(5, 1);
F_measure = zeros(5, 1);
varargin={ 'out','', 'thrs',0.1:0.1:1, 'maxDist',.0075, 'thin',1 };
for i=1:5
    [cntR1,sumR1, cntP1,sumP1] = new_edgesEvalImg(1-E, cell{i}, varargin);
    Precision(:, i) = cntP1./sumP1;
    Recall(:, i) = cntR1./sumR1;
    mean_precision(i) = mean(Precision(:,i));
    mean_recall(i) = mean(Recall(:,i));
    F_measure(i) = 2*mean_precision(i)*mean_recall(i)/(mean_precision(i) + mean_recall(i));
end
 mean_F = 2*mean(mean_precision)*mean(mean_recall)/(mean(mean_precision)+mean(mean_recall));
