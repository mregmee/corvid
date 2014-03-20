#include<vector>
class RuleTreeNode
{
public:
	int* classSupport;//support for each class for the particular item in the node
	static int classSize;
	int itemId;
	RuleTreeNode* nodeLink;
	RuleTreeNode* parent;
	RuleTreeNode()
	{
		classSupport=new int[classSize];
		for(int i=0;i<classSize;++i)
			classSupport[i]=0;
		nodeLink=NULL;
		parent=NULL;
	}
};
struct statistic
{
public:
	float sup;
	float conf;
	int count;
};
class Rule
{
public:
	statistic stat;
	std::vector<int>pattern;
};
class RuleHeaderNode
{
public:
	static int classSize;
	int* classSupport;//
	RuleTreeNode* nodeLink;
	RuleHeaderNode()
	{
		classSupport=new int[classSize];
		nodeLink=NULL;
		for(int i=0;i<classSize;++i)
			classSupport[i]=0;
	}
};
int RuleHeaderNode::classSize;
int RuleTreeNode::classSize;