const chroma = require('../index')
const utils = require('./utils')

const initialize = chroma.initialize()

if (initialize) {
  chroma.Keyboard.setReactive({red: 255, green: 0, blue: 0});
  utils.exitIn(chroma, 20000)
} else {
  console.log(`Failed to initialize!`)
}
