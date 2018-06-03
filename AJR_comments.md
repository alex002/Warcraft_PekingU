Major revision.



1. Some machine learning algorithms, such as random forest, gradient boosting, and neural network, are also good at classifying data, especially for complicated problems.  What are the benefits of using this scoring system comparing to the use of ML classifiers?

2. The scoring system is derived based on a sample of the whole population. In this case, the scoring system may overfit to this sample data and not perform well when being used to analysis other data points in the population.  Cross-validation analysis is desired to avoid this over-estimation.  An example would be separating the patient data into two groups, one to develope the scoring system/classifier, the other groups to evaluate the performance of the scoring system developed from first group.  This process can be done repeatedly or iteratively until a best scoring system is obtained.  Please discuss the cross-validation analysis of this scoring system.  If it is not required, please justify. <Please discuss the cross-validation analysis of this scoring system.>

Regarding the score metrics for optic nerve diameter:
3. Do authors expect the user to measure and determine the SD? If so, how would user get a reliable measurement of SD; If not, I would suggest simply use an absolute diameter value instead of the SD to determine the score. 

4. For diameter >= mean diameter +- 1 SD, what is the rational for using a score value of 2.5? Given that no other metric have a 0.5 score.

5. Will the optic nerve diameter differ among patients with different genders, or at different ages? In another word, will the score metric be adjusted for different genders and ages?

Regarding the score metrics for optic nerve tortuosity: 
6. Can the first four metrics be observed at the same time (interruption w/ retun, interruption w/ return, lack of congruity, and axial deviation)? 

Given the scoring system, if the optic nerve diameter is less than 2 SD from the mean, the total score will be less than 8 (OPG) even though optic nerve tortuosity is 5. On the other hand, if the optic nerve diameter is >= 2 SD from the mean, the total score will be large than 5, which is suggestive of OPG. 

