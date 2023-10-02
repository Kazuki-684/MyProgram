from django.shortcuts import render
from .contents import Bussiness, ManagementPolicyEtc, Risks, History

def judge_bool(result_dict, result):
    category = result["category"]
    result_dict[f"{category}"] = result["TorF"] 


# Create your views here.
def create_bussiness_box(result_dict, collection_name):
    bussiness = Bussiness(collection_name=collection_name)
    result = bussiness.contains_or_not()
    judge_bool(result_dict,result)
    return  result_dict


def create_management_policy_etc_box(result_dict, collection_name):
    management_policy = ManagementPolicyEtc(collection_name=collection_name)
    result = management_policy.contains_or_not()
    judge_bool(result_dict,result)
    return  result_dict


def create_bussiness_risks_box(result_dict, collection_name):
    bussiness_risks = Risks(collection_name=collection_name)
    result = bussiness_risks.contains_or_not()
    judge_bool(result_dict,result)
    return  result_dict


def create_history_box(result_dict, collection_name):
    history = History(collection_name=collection_name)
    result = history.contains_or_not()
    judge_bool(result_dict,result)
    return  result_dict

