Learning Rate should be much lower in Batch Training than Stochastic Training. It also should be inversely proportional to SampleCount. Examples:
HistoryLen=200, SampleLen=20 -> LearningRate=0.001		(MSE comes around 0.0300)
HistoryLen=1000, SampleLen=20 -> LearningRate=0.0002	(MSE comes around 0.0320)

LearningMomentum not a big deal of change...

Conversely, in Stochastic Training, Learning Rates between 0.05 and 0.2 work fine regardless of SampleCount
