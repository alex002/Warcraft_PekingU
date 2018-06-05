Major revision.

This article describes a scoring system for diagnosing optic nerve glioma in NF1 patients from MRI orbit scans.  I found the topic is of interests to the readers of this journal and this research is meaningful.  The article is generally in a good shape except some grammar errors throughout the paper.  Some details of the scoring system are not clear, and I wish the authors could elaborate:

1. Some machine learning algorithms, such as random forest, gradient boosting, and neural network, are also good at classifying data.  What are the benefits of using scoring system comparing to the use of computer classifiers?

2. What are collinearities of any two metrics in the scoring system.

Regarding the score metrics for optic nerve diameter:
3. Do users need to measure and determine the SD? If so, how would user get a reliable measurement of SD; If not, then an absolute diameter value may be better than SD. 

4. For diameter >= mean diameter + 1 SD, what is the rational for using a score of 2.5? Is the score value for each metric also determined by the ROC curve?

5. How the metrics are determined? Based on table 1, the differences in the max diameter among three groups are quite large, what are the rationals of using 1 SD and 2 SD? 

6. Will the optic nerve diameter differ among patients at different ages? In another word, do we need to adjust the score metrics for different groups of patients?

Regarding the score metrics for optic nerve tortuosity: 
7. Can the first four metrics be observed at the same time (interruption w/ retun, interruption w/ return, lack of congruity, and axial deviation)? 

8. Please provide the statistics (e.g. mean, std, range) of the scores for NF1 patients w/o OPG, NF1 patients w/ OPG, and control.

9. It is not clear where and how ROC curve was used. Please clarify. 

10. The scoring system is heavy affected by the diameter size. A >= 2 SD diameter is either "suggestive of OPG" or "OPG", while >= 1 SD can not be in the category of "OPG".  How much performance does the scoring system gain by including the optic nerve tortuosity information? Based on table 1, the classification seems to be straightforward with only the diameter information. 

Minor comments:
11. I would suggest to put a upper bound for the diameter metric. For example, >= Mean + 1 SD and < Mean + 2 SD be assigned with a score of 2.5


