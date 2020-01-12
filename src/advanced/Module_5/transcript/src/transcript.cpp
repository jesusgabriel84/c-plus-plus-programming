#include <string>
#include <list>
#include <utility>
#include <algorithm>
#include <iostream>
#include "transcript.hpp"

//Add function
void TranscriptRegistry::Add(const Transcript& t)
{
	transcript_.push_back(t);
}

//Remove function
void TranscriptRegistry::RemoveById(const std::string& id)
{
	int pos = 0;
	for (std::list<Transcript>::iterator it = transcript_.begin(); it != transcript_.end(); it++) 
	{
	    if(it->student_id == id)
	    {
	    	transcript_.erase(it);
	    	it = transcript_.begin();
	    }
	    pos++;
    }
}

//Find transcript function
std::list<Transcript>::const_iterator TranscriptRegistry::FindTranscript(const std::string& id) const
{
	
	for (std::list<Transcript>::const_iterator it = transcript_.begin(); it != transcript_.end(); it++) 
	{
	    if(it->student_id == id)
	    	return it;
    }
    return transcript_.begin();
}

//Find course results
std::list<std::pair<std::string, size_t>> TranscriptRegistry::FindCourseResults(const std::string& course) const
{
	std::list<std::pair<std::string, size_t>> results;

	for (auto& it : transcript_ )
	    for (std::list<std::pair<std::string, size_t>>::const_iterator it2 = it.grades.begin(); it2 != it.grades.end(); it2++) 
	    	if(it2->first == course)
	    		results.emplace_back(it.student_id,it2->second);
		
    return results;
}

//Get transcripts
const std::list<Transcript> TranscriptRegistry::GetTranscripts() const
{
	return this->transcript_;
}