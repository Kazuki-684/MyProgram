import ReactDom from 'react-dom/client';
import ShowFirstBox from './ShowFirstBox';

import "../stylesheets/app.scss"

const root = ReactDom.createRoot(document.getElementById('root'));

root.render(<ShowFirstBox />)