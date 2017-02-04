module.exports = {
  pressKeyToExit(chroma) {
    console.log('\nPress any key to exit\n')

    process.stdin.setRawMode(true)
    process.stdin.resume()
    process.stdin.on('data', () => {
      chroma.terminate()
      process.exit(0)
    });
  },

  exitIn(chroma, timeout) {
    timeout = timeout || 5000

    console.log(`\nExiting in ${timeout / 1000}s! \n`)

    setTimeout(() => {
      chroma.terminate()
      process.exit(0)
    }, timeout)
  }
}
