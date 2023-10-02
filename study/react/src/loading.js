import { useState, useEffect} from "react";
import ShowResultBox from "./ShowResultBox";
import axios from "axios";

const Loading = () => {
    const [showResultBox, setShowResultBox] = useState(false);
    const [result, setResult] = useState("成功！");

    useEffect( () => { 
        async function fetchData(){
        try{ 
            console.log("loadingnakadayo")
            //const res = await axios.get("http://localhost:8000/result/bool_all/");
            await axios.get("http://localhost:8000/result/bool_all/?get_a_table_of_contents").then((res) => {
                setResult(res.data);
                console.log(res);
                setShowResultBox(true);
            });   
        }catch(err){
            console.log(err);
        };
        }
        fetchData();
    },[]);

    return (
        <>
            {
            showResultBox ? 
            <ShowResultBox bool_result={result}/>
             : 
            <div className="h-screen w-screen flex justify-center items-center">
                <span className="loading loading-dots loading-lg"></span>
            </div>
            }
        </>
    );
}

export default Loading