const classes = [
    "Verb",
    "Noun"
];

async function LoadVocabulary(url) {
    const res = await fetch(url);
    return await res.text();
}


let vocabulary = null;

function argmax(list) {
    let maxArg = 0;

    for (let i = 0; i < list.length; ++i) {
        if (list[i] > list[maxArg])
            maxArg = i;
    }

    return maxArg;
}

function vocIndex(word) {
    return vocabulary.indexOf(word);
}

function genRandomVec(size) {
    const result = [];

    for (let i = 0; i < size; ++i)
        result.push(Math.random()*size/2.0 + .4);

    return result;
}


function RElu(x) {
    return Math.max(0, x);
}

function Embedding(n, size) {
    const embedding = [];
    
    for (let i = 0; i < size; ++i)
        embedding.push(RElu(randomVec1[i] * n + randomVec2[i]));

    return embedding;
}

function classifyNet(word) {
    const wordIndex = vocIndex(word);
    // first stage

    const embedding = Embedding(wordIndex, vocabulary.length);
    
    
    return [];
}

function classify(word) {
    const result = classifyNet(word);
    return classes[argmax(result)];
}

let randomVec1 = randomVec2 = [];

function init() {
    randomVec1 = genRandomVec(vocabulary.length);
    randomVec2 = genRandomVec(vocabulary.length);
    
    classify("hello");
}

LoadVocabulary("https://raw.githubusercontent.com/dwyl/english-words/master/words.txt").then((content) => {
    vocabulary = content.split("\n");
    init();
});

