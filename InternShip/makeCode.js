// フォーム要素を取得
let form = document.forms[0].elements[1];
let submitButton = document.forms[1].elements[0];

//検索するスキル
let skillData = [];

//CSVファイル読み取り用
let fileDataForCSV = undefined;

//作成されたコード用
let code= [];


function parseCSV(fileData) {
  const lines = fileData.split(/\r?\n/); // 行ごとに分割
  const result = [];

  for (let i = 0; i < lines.length; i++) {
  const row = lines[i].split(','); // カンマで列ごとに分割
  result.push(row);
    }

  return result;
}

window.addEventListener('DOMContentLoaded', (event) => {

// File APIが利用できるか確認
if(window.File && window.FileReader){
const elem_file_load = document.getElementById("file_load");

elem_file_load.addEventListener("change", (event) => {
const input_file = event.target.files[0];

// オブジェクト。ユーザーが指定したファイルを非同期で読み取る。
const f_reader = new FileReader();

// ファイル内容の読み込み(f_reader.readAsText)が正常に完了した際、コールされる
f_reader.onload = (event) => {
  const elem_file_name = document.getElementById("file_name");
  const elem_file_data = document.getElementById("file_data");

  // file名を取得
  elem_file_name.textContent += input_file.name;
  // file内容を取得
  elem_file_data.textContent = event.target.result;

  let fileData = elem_file_data.textContent;
  
  fileDataForCSV = JSON.stringify(parseCSV(fileData)); 
  };
    

// ファイル内容読み込み実施
f_reader.readAsText(input_file);

});

} else {
alert("File API is not available");
return false;
}

});


// 送信ボタンがクリックされたときのイベントリスナーを追加
form.addEventListener("click", function(event) {
  // フォームのデフォルトの送信動作をキャンセル
  event.preventDefault();

  let entForm = document.forms[0].elements[0];
  // フォームの値を取得
  let value = entForm.value;

  skillData.push(value);
  // コンソールに値を表示
  console.log("入力された値:", value);

  document.createElement("h1").innerHTML = value;

  let newElement = document.createElement("h2"); // p要素作成
  let newContent = document.createTextNode(value); // テキストノードを作成
  newElement.appendChild(newContent); // p要素にテキストノードを追加

// 親要素（div）への参照を取得
  let parentDiv = document.getElementById("skillList");

// 子要素３への参照を取得
  let childP3 = newElement;

  parentDiv.appendChild(childP3);

  entForm.value = '';
});



submitButton.addEventListener('click', e => {
  e.preventDefault();
  let skillList = skillData.join("','");
  code = `  const skillList = ['${skillList}'];
  let cssFile = [[]];
  let scouted = ${fileDataForCSV};
  
  function searchNestedArray(array, targetArray) {
      //console.log(array);
      return array.some(subArray => {
        return subArray.length === targetArray.length && subArray.every((value, index) => value === targetArray[index]);
      });
    }
    
    function createCell(index,category){
        let row = document.querySelector(\`#pane-all > div > div:nth-child(1) > div.el-table.el-table--fit.el-table--enable-row-hover.el-table--enable-row-transition > div.el-table__body-wrapper.is-scrolling-none > table > tbody > tr:nth-child(\${index})\`);
        let spans = row.children[category].getElementsByTagName('span');
    
        if(spans === undefined){
            return 'nothing';
        }
    
        let personSkills =[];
        for (let i2 = 0; i2 < spans.length; i2++) {
            let span = spans[i2];
            let text = span.textContent || span.innerText;
            personSkills.push(text);
        };
        //console.log(personSkills);
        let personSkill = personSkills.join('、');
        //console.log(personSkill);
    
        return personSkill;
    }
    
    function createPersonArray(rowNumber, row, checkButton){
        let person = [];
    
        //skill
        let skill = createCell(rowNumber,4);
        person.push(\`\${skill}\`);
    
        //position
        let position = createCell(rowNumber,3);
        person.push(\`\${position}\`);
    
        //console.log(person);
    if(scouted !== undefined){
        //console.log(\`scouted.lenght:\${scouted.length}\`);
        
        if(searchNestedArray(scouted,person)){
            row.style.backgroundColor = "grey";
            checkButton.dispatchEvent(new Event('change'));
            return 0;
        }
    }
        cssFile.push(person);
        console.log(cssFile);
        console.log(scouted);
    }
    
    //現在スタックされているデータをCSVに変換してダウンロードする
    function create_csv(cssFile) {
    
        console.log(cssFile);
    
        //作った二次元配列をCSV文字列に直す。
        let csv_string  = ""; 
        for (let d of cssFile) {
            csv_string += d.join(",");
            csv_string += '\\r\\n';
        }   
    
        //ファイル名の指定
        let time = new Date();
        let file_name   = \`scoutedPerson\${time}.csv\`;
    
        //CSVのバイナリデータを作る
        let blob        = new Blob([csv_string], {type: "text/csv"});
        let uri         = URL.createObjectURL(blob);
    
        //リンクタグを作る
        let link        = document.createElement("a");
        link.download   = file_name;
        link.href       = uri;
    
        //作ったリンクタグをクリックさせる
        document.body.appendChild(link);
        link.click();
    
        //クリックしたら即リンクタグを消す
        document.body.removeChild(link);
        delete link;
    
    }    

    for(let i = 1; i < 51; i++) {
      let temp = document.querySelector(\`#pane-all > div > div:nth-child(1) > div.el-table.el-table--fit.el-table--enable-row-hover.el-table--enable-row-transition > div.el-table__body-wrapper.is-scrolling-none > table > tbody > tr:nth-child(\${i})\`);
        //console.log(temp.children[4]);
        let spans = temp.children[4].getElementsByTagName('span');
        if(spans === undefined){
                continue;
            };
        
    
      /*中身表示する関数*/
      for (let i2 = 0; i2 < spans.length; i2++) {
        let span = spans[i2];
        let text = span.textContent || span.innerText;
          //console.log(text);
      };
        let countSkill = 0;
        
    
      /*各span要素に対して処理を行う*/
      for (let i3 = 0; i3 < skillList.length; i3++) {
        for (let i4 = 0; i4 < spans.length; i4++) {
          let span = spans[i4];
          
    
          /*span要素内のテキストを取得*/
          let text = span.textContent || span.innerText;

          /*検索文字列が含まれているかをチェック*/
          text2 = skillList[i3] + " |";
          if (text === skillList[i3] || text.startsWith(text2)) {
            /*テキスト内の検索文字列を赤くするため、HTMLを編集する*/
              span.style.color = "red";
              countSkill++;
          };
        };
        if (countSkill === skillList.length) {
          temp.style.backgroundColor = "LightGreen";
    
          let temp4 = document.querySelector(\`#pane-all > div > div:nth-child(1) > div.el-table.el-table--fit.el-table--enable-row-hover.el-table--enable-row-transition > div.el-table__body-wrapper.is-scrolling-none > table > tbody > tr:nth-child(\${i}) > td.el-table_1_column_1.el-table-column--selection > div > label > span > input\`);
          temp4.dispatchEvent(new Event('change'));
          createPersonArray(i, temp, temp4);
        };
      };
    };
    
    create_csv(cssFile);
` ;
},false);

function copyCode(code){
  navigator.clipboard.writeText(code).then(
    () => {
      // コピーに成功したときの処理
      let newElement = document.getElementById('message'); 
      let newContent = document.createTextNode('以下のコードをクリップボートにコピーしました'); // テキストノードを作成
      newElement.appendChild(newContent); 
    },
    () => {
      // コピーに失敗したときの処理
      alert('コピーに失敗しました。')
    });
}

//cellの番号をforで回す
submitButton.addEventListener('click', function(event) {
  event.preventDefault();
  let newElement = document.createElement("p"); // p要素作成
  let newContent = document.createTextNode(code); // テキストノードを作成
  newElement.appendChild(newContent); // p要素にテキストノードを追加

// 親要素（div）への参照を取得
  let parentDiv = document.getElementById("result");

// 子要素３への参照を取得
  let childP3 = newElement;
  parentDiv.appendChild(childP3);

  copyCode(code);
},false);

