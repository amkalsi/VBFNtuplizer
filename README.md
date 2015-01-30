# VBFNtuplizer
ntuplizer for susy studies
**************************************

For PHYS14 samples, follow these steps

cmsrel CMSSW_7_3_1
cd CMSSW_7_3_1/src
cmsenv
mv VBFNtuplizer/MiniAOD/ MiniAOD/
rm -rf VBFNtuplizer/
scram b -j10

cd MiniAOD/TauAnalyzerMini/python
cmsRun minoAOD.py
