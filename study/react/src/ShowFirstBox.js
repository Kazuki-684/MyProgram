import { useState } from "react"
import ShowResultBox from "./ShowResultBox";
import Loading from "./loading";

const ShowFirstBox = () => {
    const [isMounted, setIsMounted] = useState(true);

    const handleUnmount = () => {
        console.log("clicked!");
        setIsMounted(false);
    };

    return (
        <>
            {isMounted ?  (
            <div className="h-screen w-screen flex justify-center items-center">
                <div className="card w-96 bg-base-100 shadow-xl c-mainbox">
                    <div className="card-body">
                        <h2 className="card-title">Upload Document</h2>
                        <p>分析したい文章を含むファイルをアップロードしてください</p>
                        <div className="flex flex-row-reverse">
                            <button onClick={handleUnmount} className="btn btn-neutral w-1/4 bottom-0 right-0">分析する</button>
                        </div>
                    </div>
                </div>
            </div>) : <Loading />}
        </>
    );
}

export default ShowFirstBox
