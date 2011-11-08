// $Id$

#include <iostream>
#include <sstream>

#include "ScoreProducer.h"

using namespace std;

namespace Moses
{

multiset<string> ScoreProducer::description_counts;
const size_t ScoreProducer::unlimited = -1;

ScoreProducer::ScoreProducer(const std::string& description, size_t numScoreComponents)
  : m_reportSparseFeatures(false), m_numScoreComponents(numScoreComponents)
{
  description_counts.insert(description);
  size_t count = description_counts.count(description);
  ostringstream dstream;
  dstream << description;
  if (count > 1) 
  {
    dstream << ":" << count;
  }
  m_description = dstream.str();
}

ScoreProducer::~ScoreProducer() {}

const vector<FName>& ScoreProducer::GetFeatureNames() const
{
  if (m_names.size() != GetNumScoreComponents() && 
      unlimited != GetNumScoreComponents()) 
  {
    const string& desc = GetScoreProducerDescription();
    if (GetNumScoreComponents() == 1) 
    {
      m_names.push_back(FName(desc));
    }
    else 
    {
      for (size_t i = 1; i <= GetNumScoreComponents(); ++i) 
      {
        ostringstream id;
        id << i;
        m_names.push_back(FName(desc,id.str()));
      }
    }
  }
  return m_names;
}

}

