from .contents import Bussiness, ManagementPolicyEtc, Risks, History


# Create your views here.
def create_bussiness_contents(collection_name):
    bussiness = Bussiness(collection_name=collection_name)
    result = bussiness.create_content()
    return  result


def create_management_policy_etc_contents(collection_name):
    management_policy = ManagementPolicyEtc(collection_name=collection_name)
    result = management_policy.create_content()
    return  result


def create_bussiness_risks_contents(collection_name):
    bussiness_risks = Risks(collection_name=collection_name)
    result = bussiness_risks.create_content()
    return  result


def create_history_contents(collection_name):
    history = History(collection_name=collection_name)
    result = history.create_content()
    return  result
