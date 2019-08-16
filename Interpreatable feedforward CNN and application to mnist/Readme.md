# Interpreatable feedforward CNN and application to mnist
## Description:
In convolutional neural networks the model parameters are calculated using non-convex optimization method along with backpropagation technique to calculate gradients. The end-to-end interpretability of CNN is a challenge. In this problem interpretable feedforward CNN developed by Dr.C.-C. Jay Kuo has been explained. In this approach the model parameters of current layer are calculated from data statistics of output of previous layer in one-pass. New signal transform (Subspace Approximation with Adjusted Bias) has been developed to construct layers of CNN. Saab is a variant of PCA. Fully connected part of CNN is implemented using cascade of multiple least squared regressors.

## References:
1. Kuo, C. C. J., Zhang, M., Li, S., Duan, J., & Chen, Y. (2019). Interpretable convolutional neural networks via feedforward design. Journal of Visual Communication and Image Representation.
2. Chen, Y., Yang, Y., Wang, W., & Kuo, C. C. J. (2019). Ensembles of feedforward-designed convolutional neural networks. arXiv preprint arXiv:1901.02154.
3. [MNIST] http://yann.lecun.com/exdb/mnist/
4. Source code adapted from https://github.com/davidsonic/Interpretable_CNNs_via_Feedforward_Design.