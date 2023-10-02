from .base_contents import getTableOfContents
from pydantic import BaseModel,Field

#事業内容
class Bussiness(getTableOfContents):
    def __init__(self, collection_name):
        super().__init__(collection_name)
        
    class DefineVariable(BaseModel):
        bussiness :bool = Field(..., discription="Does the document include the business or not?")
        
    def contains_or_not(self):
        query = "A statement about the company's business"
        result = {"category": "事業内容", "TorF": super().contains_or_not(self.DefineVariable, query).bussiness}
        return result
    
    def create_content(self):
        query = "'instrucrion':Please describe the business of this company in an easy-to-understand format. (e.g. bulleted list) 'format':日本語で回答してください。"
        return super().create_content(query)

#経営方針、経営環境及び対処すべき課題等
class ManagementPolicyEtc(getTableOfContents):
    def __init__(self, collection_name):
        super().__init__(collection_name)
        
    class DefineVariable(BaseModel):
        management_policy_etc :bool = Field(..., discription="Does the document include the Management Policy, Business Environment, and Issues to be Addressed or not?")
        
    def contains_or_not(self):
        query = "A statement about the company's Management Policy, Business Environment, and Issues to be Addressed"
        result = {"category": "経営方針と課題", "TorF": super().contains_or_not(self.DefineVariable, query).management_policy_etc}
        return result
    
    def create_content(self):
        query = "Please describe the Management Policy, Business Environment, and Issues to be Addressed of this company in an easy-to-understand format. (e.g. bulleted list)"
        return super().create_content(query)


#経営上のリスク
class Risks(getTableOfContents):
    def __init__(self, collection_name):
        super().__init__(collection_name)
        
    class DefineVariable(BaseModel):
        bussiness_risks :bool = Field(..., discription="Does the document include the bussiness risks or not?")
        
    def contains_or_not(self):
        query = "A statement about the company's bussiness risks"
        result = {"category": "事業等のリスク", "TorF": super().contains_or_not(self.DefineVariable, query).bussiness_risks}
        return result
    
    def create_content(self):
        query = "'instruction':Please describe the risks of this company in an easy-to-understand format. (e.g. bulleted list) Please omit irrelevant content. 'format':日本語で回答してください。"
        return super().create_content(query)

    
#沿革
class History(getTableOfContents):
    def __init__(self, collection_name):
        super().__init__(collection_name)
        
    class DefineVariable(BaseModel):
        history :bool = Field(..., discription="Does the document include the History or not?")
        
    def contains_or_not(self):
        query = "A statement about the company's bussiness risks"
        result = {"category": "沿革", "TorF": super().contains_or_not(self.DefineVariable, query).history}
        return result
    
    def create_content(self):
        query = "Please describe the history of this company in an easy-to-understand format. (e.g. bulleted list)"
        return super().create_content(query)
