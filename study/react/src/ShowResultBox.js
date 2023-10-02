import { useState, useEffect, useRef} from "react";
import axios from "axios";
import { set } from "immutable";
import React from 'react';



function CategoryComponent({category, wrapper, count}) {
    const boxRef = useRef(null)
    const [content, setContent] = useState(null)
    const [isLoad, setIsLoad] = useState(false)
    
    useEffect(() => {
        if (wrapper.current) {
            console.log("もうすこしだよ")
            if (count>=6) {
                console.log("カウントされてる")
              //wrapper.current.classList.remove('');
                wrapper.current.classList.add('flex-wrap');
            }
        }

        if(boxRef.current){
            if(count>=6){
                boxRef.current.classList.remove('max-w-lg')
                boxRef.current.classList.remove('w-[400px]')
                boxRef.current.classList.add('w-56')
            }
        }
        
        axios.get(`http://localhost:8000/result/contents/?collname=get_a_table_of_contents&category=${category}`).then((res) => {
                const contents = res.data.split('\n')
                const gen_contents = contents.map((item, index) => {
                    return (
                        <React.Fragment key={index}>{item}<br /></React.Fragment>
                    );
                });
                setContent(gen_contents);
                setIsLoad(true)
            });  
        },[])

    return (
        <>
            { isLoad ? (
            <div ref={boxRef} style={{'min-width':'208px'}} className="card w-[400px] shadow-xl max-w-lg min-h-[204px] max-h-[500px] bg-white">
            <div className="card-body overflow-auto">
                <h2 className="card-title">{category}</h2>
                <div>
                    <p>{content}</p>
                </div>
            </div>
            </div> ):
             <div ref={boxRef} style={{'min-width':'208px'}} className="card w-[400px] shadow-xl max-w-lg min-h-[204px] max-h-[500px] bg-white">
             <div className="card-body overflow-auto">
                <h2 className="card-title">{category}</h2>
                <span className="loading loading-dots loading-sm"></span>
             </div>
             </div> 
            }   
        </>
    );
  }


const ShowResultBox = ({bool_result}) => {
    const countBox = useRef(1);
    const count = countBox.current;
    const wrapperElementRef = useRef(null);

    useEffect(()=>{
     const wrapperElement = wrapperElementRef.current;
     console.log(wrapperElementRef.current)
    })
    
    const categories = Object.keys(bool_result)

    
    return (
        <div ref={wrapperElementRef} className="flex justify-center items-center flex-row h-screen w-screen gap-3 px-10">
          {categories.map(category => {
            if (bool_result[category]) {
              return (
                <CategoryComponent
                  key={category}
                  count={countBox.current++}
                  wrapper={wrapperElementRef}
                  category={category}
                />
              );
            }
            return null; // Skip rendering for categories with false values
          })}
        </div>
      );
    };

export default ShowResultBox